// Copyright distributed.net 1997-1998 - All Rights Reserved
// For use in distributed.net projects only.
// Any other distribution or use of this source violates copyright.
//
/* This file contains functions for getting/setting/clearing
   "mode" request from GUI menus and the like. Client::Run() 
   will clear/run the modes when appropriate.
*/    
//
// $Log: modereq.cpp,v $
// Revision 1.4  1998/11/02 04:46:08  cyp
// Added check for user break after each mode is processed. Added code to
// automatically trip a restart after mode processing (for use with config).
//
// Revision 1.3  1998/10/11 02:45:20  cyp
// Added &= ~(MODEREQ_CONFIG) that I forgot.
//
// Revision 1.2  1998/10/11 00:40:11  cyp
// Added MODEREQ_CONFIG.
//
// Revision 1.1  1998/10/08 20:49:41  cyp
// Created.
//
#if (!defined(lint) && defined(__showids__))
const char *modereq_cpp(void) {
return "@(#)$Id: modereq.cpp,v 1.4 1998/11/02 04:46:08 cyp Exp $"; }
#endif

#include "client.h"   //client class
#include "triggers.h" //CheckExitRequestTrigger() [used by bench stuff]
#include "logstuff.h" //LogScreen() [used by update/fetch/flush stuff]
#include "modereq.h"  //our constants
#include "triggers.h" //RaiseRestartRequestTrigger/CheckExitRequestTriggerNoIO
#include "console.h"  //Clear the screen after config if restarting

#include "cpucheck.h" //"mode" DisplayProcessorInformation()
#include "cliident.h" //"mode" CliIdentifyModules();
#include "selftest.h" //"mode" SelfTest()
#include "bench.h"    //"mode" Benchmark()


/* --------------------------------------------------------------- */

static struct
{
  int isrunning;
  int reqbits;
} modereq = {0,0};

/* --------------------------------------------------------------- */

int ModeReqIsSet(int modemask)
{
  return ((modereq.reqbits & modemask) != 0);
}

/* --------------------------------------------------------------- */

int ModeReqSet(int modemask)
{
  if (modemask == -1)
    modemask = MODEREQ_ALL;
  int oldmask = (modereq.reqbits & modemask);
  modereq.reqbits |= modemask;
  return oldmask;
}

/* --------------------------------------------------------------- */

int ModeReqClear(int modemask)
{
  int oldmask;
  if (modemask == -1)
    {
    oldmask = modereq.reqbits;
    modereq.reqbits = 0;
    }
  else
    {
    modemask &= MODEREQ_ALL;
    oldmask = (modereq.reqbits & modemask);
    modereq.reqbits ^= (modereq.reqbits & modemask);
    }
  return oldmask;
}

/* --------------------------------------------------------------- */

int ModeReqIsRunning(void)
{
  return (modereq.isrunning != 0);
}

/* --------------------------------------------------------------- */

int ModeReqRun(Client *client)
{
  int retval = 0;
  
  if (++modereq.isrunning == 1)
    {
    int restart = ((modereq.reqbits & MODEREQ_RESTART)!=0);
    modereq.reqbits &= ~MODEREQ_RESTART;
    
    while ((modereq.reqbits & MODEREQ_ALL)!=0)
      {
      unsigned int bits = modereq.reqbits;
    
      if ((bits & (MODEREQ_BENCHMARK_DES | MODEREQ_BENCHMARK_RC5)) != 0)
        {
        if (client)
          {
          u32 benchsize = (1L<<23); /* long bench: 8388608 instead of 100000000 */
          if ((bits & (MODEREQ_BENCHMARK_QUICK))!=0)
            benchsize = (1L<<20); /* short bench: 1048576 instead of 10000000 */
          if ( !CheckExitRequestTriggerNoIO() && (bits&MODEREQ_BENCHMARK_RC5)!=0)
            Benchmark( 0, benchsize, client->cputype );
          if ( !CheckExitRequestTriggerNoIO() && (bits&MODEREQ_BENCHMARK_DES)!=0)
            Benchmark( 1, benchsize, client->cputype );
          }
        retval |= (modereq.reqbits & (MODEREQ_BENCHMARK_DES | 
                 MODEREQ_BENCHMARK_RC5 | MODEREQ_BENCHMARK_QUICK ));
        modereq.reqbits &= ~(MODEREQ_BENCHMARK_DES | 
                 MODEREQ_BENCHMARK_RC5 | MODEREQ_BENCHMARK_QUICK );
        }
      if ((bits & (MODEREQ_CONFIG | MODEREQ_CONFRESTART)) != 0)
        {
        if ( client->Configure() == 1 )
          {
          client->WriteFullConfig(); //full new build
          }
        if ((bits & MODEREQ_CONFRESTART) != 0)
          restart = 1;
        retval |= (bits & (MODEREQ_CONFIG|MODEREQ_CONFRESTART));
        modereq.reqbits &= ~(MODEREQ_CONFIG|MODEREQ_CONFRESTART);
        }
      if ((bits & (MODEREQ_FETCH | MODEREQ_FLUSH))!=0)
        {
        int dofetch = (bits & (MODEREQ_FETCH));
        int doflush = (bits & (MODEREQ_FLUSH));
        int doforce = (bits & (MODEREQ_FFORCE));
        s32 oldofflinemode; 
        unsigned char contest;
        int runcode, retcode = 0;

        if (client)
          {
          oldofflinemode = client->offlinemode;
          client->offlinemode=0;
          for (contest=0;contest<2;contest++)
            {
            if (!(client->contestdone[contest]))
              {
              runcode = 0;
              if ( dofetch & doflush )
                runcode=(int)(client->Update(contest ,1,1, doforce));
              else if ( dofetch )
                runcode=(int)((doforce)?(client->ForceFetch(contest)):(client->Fetch(contest)));
              else
                runcode=(int)((doforce)?(client->ForceFlush(contest)):(client->Flush(contest)));
              if (client->randomchanged) 
                client->WriteContestandPrefixConfig();
              if (!(client->contestdone[contest]) && runcode < retcode) 
                retcode = runcode;
              if (runcode == -2) //no network
                break;
              }
            }
          client->offlinemode = oldofflinemode;
          }
     
        if (retcode < 0)
          {
          //unless it was a network error, fetch/flush/update will already
          //have printed the cause for the "error", so don't say anything here.
          if (retcode == -2)
            {
            LogScreen( "Network services are not available or not supported.\n"
                       "TCP/IP network services are required for the flush,\n"
                       "forceflush, fetch, forcefetch or update options." );
            }
          retcode = -1;
          }
        else
          {
          //fetch/flush/update will already have said something.
          //thisarg[1] = (char)toupper(thisarg[1]);
          //LogScreen( "%s completed.\n", thisarg+1 );
          retcode = 0;
          }
  
        retval |= (modereq.reqbits & (MODEREQ_FETCH | MODEREQ_FLUSH | 
                               MODEREQ_FFORCE));
        modereq.reqbits &= ~(MODEREQ_FETCH | MODEREQ_FLUSH | MODEREQ_FFORCE);
        }
      if ((bits & MODEREQ_IDENT)!=0)    
        {
        CliIdentifyModules();
        modereq.reqbits &= ~(MODEREQ_IDENT);
        retval |= (MODEREQ_IDENT);
        }
      if ((bits & MODEREQ_CPUINFO)!=0)
        {
        DisplayProcessorInformation(); 
        modereq.reqbits &= ~(MODEREQ_CPUINFO);
        retval |= (MODEREQ_CPUINFO);
        }
      if ((bits & MODEREQ_TEST)!=0)
        {
        if (client)
          {
          if ( SelfTest(0, client->cputype ) > 0 ) 
            SelfTest(1, client->cputype );
          }
        retval |= (MODEREQ_TEST);
        modereq.reqbits &= ~(MODEREQ_TEST);
        }
      if (CheckExitRequestTriggerNoIO())
        {
        restart = 0;
        break;
        }
      } //end while
    
    if (restart)
      RaiseRestartRequestTrigger();
    } //if (++isrunning == 1)

  modereq.isrunning--;
  return retval;
}

