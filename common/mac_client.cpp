// Copyright distributed.net 1997-1999 - All Rights Reserved
// For use in distributed.net projects only.
// Any other distribution or use of this source violates copyright.
//
// $Log: mac_client.cpp,v $
// Revision 1.10  1999/03/23 06:13:04  dicamillo
// Additions to InitializeClient code.
//
// Revision 1.9  1999/03/22 08:08:53  dicamillo
// Update InitializeTriggers calls.
//
// Revision 1.8  1999/03/01 16:14:21  sampo
// Update to accomadate change in ContestWork union
//
// Revision 1.7  1999/01/16 22:00:41  sampo
// change for fba (#include "clirate.h") so it will compile.
//
// Revision 1.6  1999/01/07 03:19:06  dicamillo
// Add ReInitializeClient method.
//
// Revision 1.5  1999/01/01 02:45:15  cramer
// Part 1 of 1999 Copyright updates...
//
// Revision 1.4  1998/12/16 22:40:31  dicamillo
// Fixed commenting error (missing //) in previous log entry.
//
// Revision 1.3  1998/12/16 15:57:17  sampo
// MODEREQ_FFORCE doesn't do anything different from normal force/flush, so I
// recycled it as MODEREQ_FQUIET for use with non-interactive BufferUpdate()
//
// Revision 1.2  1998/12/15 07:01:49  dicamillo
// Use "_" instead of "/" in Mac header file names for CVS.
//
// Revision 1.1  1998/12/14 00:03:43  dicamillo
// First Checked In.
//
#if (!defined(lint) && defined(__showids__))
const char *mac_client_cpp(void) {
return "@(#)$Id: mac_client.cpp,v 1.10 1999/03/23 06:13:04 dicamillo Exp $"; }
#endif

// This file contains the routines added to the Client class for the Mac_Client
// class the Mac client uses.  Some methods here are likely to require changes when
// related code is changed in the "common" files.

#if (CLIENT_OS == OS_MACOS)

#include "client.h"
#include "problem.h"
#include "modereq.h"
#include <machine_endian.h>
#include "triggers.h"
#include "console.h"
#include "probman.h"
#include "problem.h"
#include "logstuff.h"
#include "pathwork.h"
#include "Mac_Client.h"
#include "String.h"
#include "clirate.h"
#include "random.h"
#if defined(MAC_GUI)
#include "DrawGUI.h"
#endif

int InitializeConnectivity(void);	// from client.cpp
int DeinitializeConnectivity(void);
void YieldToMain(char force_events);
extern FCBPBRec myFCB;		// FCB for this program
void PrintBanner(const char *dnet_id,int level,int restarted);

#define TEST_CASE_COUNT 32

#if defined(MAC_GUI)
extern ClientInfo client_info;
void UpdateThreadProgress(short cpunum, short percent, unsigned long keys,
		Boolean benchmark);
void UpdateClientInfo(ClientInfo *theInfo);
void SetStatusMessage(char *text);
void MakeGUIThread(short contest, short cpunum);
void DestroyGUIThread(short cpunum);
void DestroyAllGUIThreads(void);
double CliGetKeyrateForProblemNoSave( Problem *prob );
#endif

int Mac_Client::InitializeClient(void)
{
	int retcode = 0;
	int my_argc = 1;
	char *my_argv[] = {"rc5des"};
      
	this->Client();  /* reset everything in the object */

	if (ParseCommandline( 0, my_argc, my_argv, &retcode, 0 ) != 0) {
		return(1);
	}
	  
	int domodes = (ModeReqIsSet(-1) != 0);
	if (InitializeTriggers(((noexitfilecheck ||
							domodes)?(NULL):("exitrc5" EXTN_SEP "now")),
							((domodes)?(NULL):(pausefile)) )!=0) {
		return(2);
	}
	if (InitializeConnectivity() != 0) {
		return(3);
	}
	if (InitializeConsole(0, 0) != 0) {
		return(4);
	}	
    InitializeLogging( (quietmode!=0), (percentprintingoff!=0), 
                       logname, LOGFILETYPE_NOLIMIT, 0, messagelen, 
                       smtpsrvr, smtpport, smtpfrom, smtpdest, id );

	ParseCommandline( 1, my_argc, my_argv, NULL, true); //show overrides

	InitRandom2( id );

	return(0);
}

void Mac_Client::ReInitializeClient(void)
{
((Client *)this)->Client();
}

void Mac_Client::ResetClient(void)
{
	DeinitializeTriggers();
    int domodes = (ModeReqIsSet(-1) != 0);
    InitializeTriggers(((noexitfilecheck ||
                         domodes)?(NULL):("exitrc5" EXTN_SEP "now")),
                         ((domodes)?(NULL):(pausefile)) );
}

void Mac_Client::DeInitializeClient(void)
{
	DeinitializeLogging();
	DeinitializeConsole();
	DeinitializeConnectivity();
	DeinitializeTriggers();
}

double Mac_Client::TimeCore(u32 numk, short core)
{
// Note: we only do timimg with the RC5 cores, which can do a specified
// number of iterations

Problem problem;
ContestWork contestwork;

contestwork.crypto.key.lo = contestwork.crypto.key.hi = htonl( 0 );
contestwork.crypto.iv.lo = contestwork.crypto.iv.hi = htonl( 0 );
contestwork.crypto.plain.lo = contestwork.crypto.plain.hi = htonl( 0 );
contestwork.crypto.cypher.lo = contestwork.crypto.cypher.hi = htonl( 0 );
contestwork.crypto.keysdone.lo = contestwork.crypto.keysdone.hi = htonl( 0 );
contestwork.crypto.iterations.lo = htonl( numk );
contestwork.crypto.iterations.hi = htonl( 0 );
problem.LoadState( &contestwork, 0, numk, core ); // RC5 core selection
problem.Run( 0 ); //threadnum

return( CliGetKeyrateForProblemNoSave( &problem ) );
}

s32 Mac_Client::Startup( int argc, char *argv[] )
{
  int run_result;
  Boolean do_modes = false;
  
  offlinemode = 0;

  // parse argument
  if (argc > 1 ) {
    if ( strcmp( argv[1], "-test" ) == 0 )
    {
		ModeReqClear(-1); //clear all - only do -test
		ModeReqSet( MODEREQ_TEST );
		do_modes = true;
    }
    else if ( strcmp( argv[1], "-benchmarkRC5" ) == 0 )
    {
        ModeReqClear(-1); //clear all - only do benchmark
        ModeReqSet( MODEREQ_BENCHMARK_RC5 );
		do_modes = true;
    }
    else if ( strcmp( argv[1], "-benchmarkDES" ) == 0 )
    {
        ModeReqClear(-1); //clear all - only do benchmark
        ModeReqSet( MODEREQ_BENCHMARK_DES );
		do_modes = true;
    }
    else if (( strcmp( argv[1], "-fetch" ) == 0 ) || ( strcmp( argv[1], "-forcefetch" ) == 0 ))
    {
        ModeReqClear(-1); //clear all - only do -fetch/-flush/-update
        ModeReqSet( MODEREQ_FETCH );
		do_modes = true;	
    }
    else if (( strcmp( argv[1], "-flush" ) == 0 ) || ( strcmp( argv[1], "-forceflush" ) == 0 ))
    {
        ModeReqClear(-1); //clear all - only do -fetch/-flush/-update
        ModeReqSet( MODEREQ_FLUSH );
		do_modes = true;
    }
    else if ( strcmp( argv[1], "-update" ) == 0 )
    {
        ModeReqClear(-1); //clear all - only do -fetch/-flush/-update
        ModeReqSet( MODEREQ_FETCH | MODEREQ_FLUSH | MODEREQ_FQUIET );
		do_modes = true;
    }
    else if ( strcmp( argv[1], "-runoffline" ) == 0 )
    {
		  offlinemode = 1;
    }
    else if ( strcmp( argv[1], "-runbuffers" ) == 0 )
    {
		  blockcount = -1;
    }
    else return (0);
  }

  if (do_modes) {
 	 run_result = ModeReqRun( this );
  }
  else {
     PrintBanner(id,1,1);
     SelectCore( 0 );
	 run_result = Run();
  }    

#if defined(MAC_GUI)
// delete any GUI threads
  DestroyAllGUIThreads();
#endif

  return run_result;
}

void Mac_Client::UpdateFileDates(void)
{
file_dates[0] = GetFileDate(in_buffer_file[0]);
file_dates[1] = GetFileDate(out_buffer_file[0]);
file_dates[2] = GetFileDate(in_buffer_file[1]);
file_dates[3] = GetFileDate(out_buffer_file[1]);
}

unsigned long Mac_Client::GetFileDate(char *filename)
{
HParamBlockRec hpb;
Str255 finfo_name;
OSErr rc;

memset(&hpb, 0, sizeof(HParamBlockRec));
strcpy((char *)finfo_name, filename);
c2pstr((char *)finfo_name);
hpb.fileParam.ioNamePtr = finfo_name;
hpb.fileParam.ioVRefNum = myFCB.ioFCBVRefNum;
hpb.fileParam.ioDirID = myFCB.ioFCBParID;
rc = PBHGetFInfoSync(&hpb);

if (rc == noErr) {
	return(hpb.fileParam.ioFlMdDat);
	}
else {
	return(0);
	}
}

Boolean Mac_Client::ChangedFileDates(void)
{
unsigned long new_dates[4];
Boolean result;

new_dates[0] = GetFileDate(in_buffer_file[0]);
new_dates[1] = GetFileDate(out_buffer_file[0]);
new_dates[2] = GetFileDate(in_buffer_file[1]);
new_dates[3] = GetFileDate(out_buffer_file[1]);

result = memcmp(file_dates, new_dates, sizeof(new_dates)) != 0;

memcpy(file_dates, new_dates, sizeof(new_dates));
return(result);
}

// following routines for GUI version only
#if defined(MAC_GUI)

void Mac_Client::RefreshBufferCounts(void)
{
short project;

for (project = 0; project < 2; project++) {
	client_info.buffersInfo[project].inputBuffer.numBlocks =
    client_info.buffersInfo[project].inputBuffer.totalBlocks =
    	GetBufferCount(project, 0, 0);
	if (inthreshold[project] >
			client_info.buffersInfo[project].inputBuffer.numBlocks) {
		client_info.buffersInfo[project].inputBuffer.totalBlocks =
			inthreshold[project];
		}
	client_info.buffersInfo[project].inputBuffer.changingRightNow = false;

	client_info.buffersInfo[project].outputBuffer.numBlocks =
    client_info.buffersInfo[project].outputBuffer.totalBlocks =
    	GetBufferCount(project, 1, 0);
	if (outthreshold[project] >
			client_info.buffersInfo[project].outputBuffer.numBlocks) {
		client_info.buffersInfo[project].outputBuffer.totalBlocks =
			outthreshold[project];
		}
	client_info.buffersInfo[project].outputBuffer.changingRightNow = false;
	}

UpdateFileDates();
}

void Mac_Client::UpdateProblemStatus(unsigned int problem_count)
{
    unsigned long new_gui_ticks = LMGetTicks();
	static unsigned long last_gui_ticks = 0;
	unsigned int prob_i;
	Problem *selprob;
	Boolean need_yield = false;
	Boolean expired = false;
	
  	for (prob_i = 0; prob_i < problem_count; prob_i++) {
		if ((new_gui_ticks - last_gui_ticks) > 300) {
			expired = true;
     		selprob = GetProblemPointerFromIndex(prob_i);
			UpdateThreadProgress(prob_i, selprob->CalcPercent(),
				selprob->GetKeysDone(), false);
		}
		if (selprob->started && (selprob->contest == 0)) {
			need_yield = true;
		}
	}

	if (expired) {
		last_gui_ticks = new_gui_ticks;
		UpdateClientInfo(&client_info);
		}
    if (need_yield) YieldToMain(1);
}

#endif defined(MAC_GUI)
#endif (CLIENT_OS == OS_MACOS)
