/* Copyright distributed.net 1998-1999 - All Rights Reserved
 * For use in distributed.net projects only.
 * Any other distribution or use of this source violates copyright.
 * Written by Cyrus Patel <cyp@fb14.uni-mainz.de>
 *
 * ----------------------------------------------------------------------
 * This file contains functions for formatting keyrate/time/summary data
 * statistics obtained from clirate.cpp into strings suitable for display.
 * ----------------------------------------------------------------------
*/ 
const char *clisrate_cpp(void) {
return "@(#)$Id: clisrate.cpp,v 1.45.2.6 1999/12/16 19:24:28 cyp Exp $"; }

#include "cputypes.h"  // u32
#include "problem.h"   // Problem class
#include "client.h"    // Fileentry struct
#include "baseincs.h"  // timeval, sprintf et al
#include "clitime.h"   // CliTimer(), CliTimerDiff(), CliGetTimeString()
#include "clirate.h"   // CliGetKeyrateFor[Problem|Contest]()
#include "clicdata.h"  // CliGetContestInfo[Base|Summary]Data()
#include "util.h"      // temporary home of ogr_stubstr()
#include "clisrate.h"  // keep prototypes in sync

/*
 *
 * Synopsis:
 *
 *  char *num_sep(char *number)
 *
 * Description:
 *
 *  This routine takes a string which actually represents a number
 *  for instance "1234567" and converts it to "1,234,567". Effectively
 *  it adds a comma for each 3 digits. The function checks whether
 *  a 'fractional part' indicated by a '.' is present and takes care
 *  of this by skipping the '.', the fraction, and whatever follows
 *  the fraction.
 *
 * Known Side Effects:
 *
 *  The function currently does not work correctly if 'number' points
 *  to a string with some other characters prefixed to the number in
 *  question. It also doesn't work, if the 'number' string is a pure
 *  integer without a fraction and is still postfixed with some non-number
 *  data.
 *
 * Return Value:
 *
 *  Good case:
 *     char * to buffer with number separators inserted.
 *
 *  Bad case:
 *     char *number (exactly what it got as input) The bad case happens
 *                  if the input points to a huge string which would
 *                  cause a buffer overflow during processing of the
 *                  input data.
 *
 */

static const char *num_sep(const char *number)
{
  static char num_string[(sizeof(long)*3*2) + 1];

  char *rp, *wp, *xp;             /* read ptr, write ptr, aux ptr */
  register unsigned int digits;
  register unsigned int i, j;

  /*
   * just in case somebody passes a pointer to a long string which
   * then obviously holds much more than just a number. In this case
   * we simply return what we got and don't do anything.
   */

  digits = strlen(number);

  if (digits >= (sizeof(num_string)-1))
    return number;

  strcpy(num_string, number);
  rp = num_string + digits - 1;
  wp = num_string + (sizeof(num_string)-1);
  *wp-- = '\0';
  if ((xp = strchr(num_string, '.')) != NULL) {
    while (rp >= xp) {
      *wp-- = *rp--;
      digits--;
    }
  }
  for (i = digits, j = 1; i; i--, j++) {
    *wp-- = *rp--;
    if (j && ((j % 3) == 0))
      *wp-- = ',';
  }
  if (wp[1] == ',')
    wp++;
  return (wp + 1);
}


// ---------------------------------------------------------------------------

// returns keyrate as string (len<=26) "nnnn.nn ['K'|'M'|'G'|'T']"
// return value is a pointer to buffer.
static char *__CliGetKeyrateAsString( char *buffer, double rate, double limit )
{
  if (rate<=((double)(0)))  // unfinished (-2) or error (-1) or impossible (0)
    strcpy( buffer, "---.-- " );
  else
  {
    unsigned int t1, t2 = 0;
    const char *t3[]={"","k","M","G","T"}; // "", "kilo", "mega", "giga", "tera"
    while (t2<=5 && (((double)(rate))>=((double)(limit))) )
    {
      t2++;
      rate = ((double)(rate)) / ((double)(1000));
    }
    if (t2 > 4)
      strcpy( buffer, "***.** " ); //overflow (rate>1.0 TKeys. Str>25 chars)
    else
    {
      t1 = (unsigned int)(rate);
      sprintf( buffer, "%u.%02u %s", t1,
         ((unsigned int)((((double)(rate-((double)(t1)))))*((double)(100)))),
         t3[t2] );
    }
  }
  return buffer;
}

// returns keyrate as string (len<=26) "nnnn.nn ['k'|'M'|'G'|'T']"
// return value is a pointer to buffer.
const char *CliGetKeyrateAsString( char *buffer, double rate )
{ 
  return (num_sep(__CliGetKeyrateAsString( buffer, rate, _U32LimitDouble_ )));
}

// ---------------------------------------------------------------------------

// "4 RC5 packets 12:34:56.78 - [234.56 Kkeys/s]" 
const char *CliGetSummaryStringForContest( int contestid )
{
  static char str[70];
  char keyrate[32];
  double totaliter;
  const char *keyrateP, *name;
  unsigned int packets, units;
  struct timeval ttime;

  if ( CliIsContestIDValid( contestid ) ) //clicdata.cpp
  {
    CliGetContestInfoBaseData( contestid, &name, NULL ); //clicdata.cpp
    CliGetContestInfoSummaryData( contestid, &packets, &totaliter, &ttime, &units ); //ditto
    keyrateP=__CliGetKeyrateAsString(keyrate,
          CliGetKeyrateForContest(contestid),((double)(1000)));
  }
  else
  {
    name = "???";
    units = packets = 0;
    ttime.tv_sec = 0;
    ttime.tv_usec = 0;
    keyrateP = "---.-- ";
  }

  str[0] = '\0';
  switch (contestid)
  {
    case RC5:
    case DES:
    case CSC:
    {
      sprintf(str, "%d %s packet%s (%u*2^28 work units)\n"
                   "%s%c- [%s%s/s]", 
           packets, name, ((packets==1)?(""):("s")), units,
           CliGetTimeString( &ttime, 2 ), ((!packets)?(0):(' ')), keyrateP,
           contestid == OGR ? "nodes" : "keys" );
      break;
    }
    case OGR:  /* old style */
    {
      sprintf(str, "%d %s packet%s %s%c- [%s%s/s]", 
           packets, name, ((packets==1)?(""):("s")),
           CliGetTimeString( &ttime, 2 ), ((!packets)?(0):(' ')), keyrateP,
           contestid == OGR ? "nodes" : "keys" );
      break;
    }
  }

  return str;
}

// ---------------------------------------------------------------------------

// return iter/keysdone/whatever as string. 
// set contestID = -1 to have the ID ignored
const char *CliGetU64AsString( u32 norm_hi, u32 norm_lo, 
                               int /*inNetOrder*/, int contestid )
{
  static char str[32];
  unsigned int i;
  double d;

  d = U64TODOUBLE(norm_hi, norm_lo);
  if (CliGetContestInfoBaseData( contestid, NULL, &i )==0 && i>1) //clicdata
    d = d * ((double)(i));

  i = 0;
  norm_hi = (unsigned int)(d / 1000000000.0);
  norm_lo = (unsigned int)(d - (((double)(norm_hi))*1000000000.0));
  d = d / 1000000000.0;
  if (d > 0)
  {
    i = (unsigned int)(d / 1000000000.0);
    norm_hi = (unsigned int)(d - (((double)(i))*1000000000.0));
  }

  if (i)            sprintf( str, "%u%09u%09u", (unsigned) i, (unsigned) norm_hi, (unsigned) norm_lo );
  else if (norm_hi) sprintf( str, "%u%09u", (unsigned) norm_hi, (unsigned) norm_lo );
  else              sprintf( str, "%u", (unsigned) norm_lo );

  return str;
}

// ---------------------------------------------------------------------------

// internal - with or without adjusting cumulative stats
// Completed RC5 packet 68E0D85A:A0000000 (123456789 keys)
//          123:45:67:89 - [987654321 keys/s]
// Completed OGR stub 22/1-3-5-7 (123456789 nodes)
//          123:45:67:89 - [987654321 nodes/s]
static const char *__CliGetMessageForProblemCompleted( Problem *prob, int doSave )
{
  static char str[160];
  ContestWork work;
  struct timeval tv;
  char keyrate[64];
  unsigned int /* size=1, count=32, */ itermul;
  unsigned int mulfactor, contestid = 0;
  const char *keyrateP = "---.-- ", *name = "???";
  int resultcode = prob->RetrieveState( &work, &contestid, 0 );

  if (resultcode != RESULT_NOTHING && resultcode != RESULT_FOUND)
  {
    memset((void *)&work,0,sizeof(work));
    tv.tv_sec = tv.tv_usec = 0;
  }
  else
  {
    if (CliGetContestInfoBaseData( contestid, &name, &mulfactor )==0) //clicdata
    {
      keyrateP = __CliGetKeyrateAsString( keyrate, 
          ((doSave) ? ( CliGetKeyrateForProblem( prob ) ) :
                      ( CliGetKeyrateForProblemNoSave( prob ) )),
                      _U32LimitDouble_ );
      keyrateP = (const char *)strcpy( keyrate, num_sep( keyrateP ) );
    }
    /*  
    tv.tv_sec = prob->timehi;
    tv.tv_usec = prob->timelo;
    CliTimerDiff( &tv, &tv, NULL );
    */
    //tv.tv_sec = prob->runtime_sec;  //thread user time
    //tv.tv_usec = prob->runtime_usec;
    tv.tv_sec = prob->completion_timehi;  //wall clock time
    tv.tv_usec = prob->completion_timelo;
  }
  
  switch (contestid) 
  {
    case RC5:
    case DES:
    case CSC:
//"Completed RC5 packet 00000000:00000000 (4*2^28 keys)\n"
//"%s - [%skeys/sec]\n"
      itermul = (((work.crypto.iterations.lo) >> 28) +
                 ((work.crypto.iterations.hi) <<  4) );
      sprintf( str, "Completed %s packet %08lX:%08lX (%u*2^28 keys)\n"
                    "%s - [%skeys/sec]\n",  
                    name, 
                    (unsigned long) ( work.crypto.key.hi ) ,
                    (unsigned long) ( work.crypto.key.lo ),
                    (unsigned int)(itermul),
                    CliGetTimeString( &tv, 2 ),
                    keyrateP );
      break;
    case OGR:
//[Nov 12 16:20:35 UTC] Completed OGR stub 23/21-16-11-31 (17,633,305,532 nodes)
//"%s - [%skeys/sec]\n"
      sprintf( str, "Completed %s stub %s (%s nodes)\n"
                    "%s - [%snodes/sec]\n",  
                    name, 
                    ogr_stubstr( &work.ogr.workstub.stub ),
                    num_sep(CliGetU64AsString(work.ogr.nodes.hi, 
                                              work.ogr.nodes.lo, 0, -1)),
                    CliGetTimeString( &tv, 2 ),
                    keyrateP );
      break;
  }
  return str;
}

// Completed RC5 packet 68E0D85A:A0000000 (123456789 keys)
//          123:45:67:89 - [987654321 keys/s]
const char *CliGetMessageForProblemCompleted( Problem *prob )
{ return __CliGetMessageForProblemCompleted( prob, 1 ); }

const char *CliGetMessageForProblemCompletedNoSave( Problem *prob )
{ return __CliGetMessageForProblemCompleted( prob, 0 ); }

// ---------------------------------------------------------------------------

