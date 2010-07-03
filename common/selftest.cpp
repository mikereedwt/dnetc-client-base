/*
 * Copyright distributed.net 1997-2009 - All Rights Reserved
 * For use in distributed.net projects only.
 * Any other distribution or use of this source violates copyright.
*/
const char *selftest_cpp(void) {
return "@(#)$Id: selftest.cpp,v 1.103 2010/07/03 13:25:36 stream Exp $"; }

#include "cputypes.h"
#include "client.h"    // CONTEST_COUNT
#include "baseincs.h"  // standard #includes
#include "problem.h"   // Problem class
#include "triggers.h"  // CheckExitRequestTriggerNoIO()
#include "logstuff.h"  // LogScreen()
#include "cpucheck.h"  // GetNumberOfDetectedProcessors() [for RISCOS]
#include "clicdata.h"  // CliGetContestNameFromID()
#include "clievent.h"  // ClientEventSyncPost()
#include "selftest.h"

// --------------------------------------------------------------------------

#define TEST_CASE_COUNT 32
#define TEST_CASE_DATA  10

// note this is in .lo, .hi, .lo... order...

#ifdef HAVE_RC5_72_CORES
// RC5-32/12/9 test cases -- generated by gentests72.cpp:
static const u32 rc5_72_test_cases[TEST_CASE_COUNT][TEST_CASE_DATA] = { // seed = 982
  {0x000000C9,0x0C0353C0,0xD4E1FE85,0x1F59CE07,0x419A1486,0x20656854,0x6E6B6E75,0x562D285A,0x2FB7852A,0x00000001}, // 0111 official RSA testcase ?
  {0x000000DE,0xEE0C6279,0xBF66F898,0x8F0FC4D4,0x5C7BE413,0x1850EA58,0x0E02AEE8,0x9D745D16,0xB796FAAB,0x00000001}, // 0020
  {0x0000000F,0x556979E7,0x6C009260,0xE72C642E,0x0E04E4B2,0x6ABACC4B,0x1D8EDBC6,0x9C0C50A7,0x2D44E127,0x00000001}, // 0010 increment
  {0x0000009E,0xD8B648C6,0x00003A3C,0x776E94A7,0xC5DB4564,0x128A1B81,0x02571D50,0x313F939B,0x55CD7EC3,0x00000001}, // 0010 increment
  {0x000000C8,0xB3631100,0x0000EAF0,0x47CCD4B9,0x6269DF39,0x58EDDE48,0x6F32CEBB,0x2C35BB51,0x4B79164F,0x00000001}, // 0000 increment
  {0x000000FE,0x40080000,0x00006F64,0xC8CDE36E,0xE1B8EF64,0x95B4A79E,0x4605BD3C,0xE72B0870,0x80EB3E89,0x00000001}, // 0010 increment
  {0x00000028,0x69000000,0x0000204D,0x45214BFC,0xD9B533E2,0xDF213C23,0xA6CA9EA4,0x47BA33D7,0xDFFE0F22,0x00000001}, // 0111 increment
  {0x0000006E,0x00000000,0x0000172F,0x6D61CA35,0x3094B27F,0x29A70EB2,0x472B3E2B,0xF069F77B,0x50DBB2D9,0x00000001}, // 0113 increment
  {0x000000C6,0xE9386A44,0xC0F9D107,0x580D9BFA,0x545B2D79,0xDAB8806E,0xBAC12504,0x11D572B7,0x5DA4EDC8,0x00000001}, // 0123
  {0x0000002B,0xE01C5B9D,0xD65CCAD7,0xFA04DE75,0x5C690280,0x42E9EF80,0xFDCE3666,0x50E44FCA,0x9474751F,0x00000001}, // 0123
  {0x00000097,0x2C0F244D,0xEFC54E4F,0x61782CEA,0x8EBEEAA2,0xA997FC19,0x637EFE8D,0x6D8BA543,0x829162D6,0x00000001}, // 0113
  {0x000000A8,0x8960B40B,0x1F46AD1F,0x635AAE06,0x4D71F94C,0xE31C9102,0xA3710F1D,0xBBC7380B,0x3A2B26DE,0x00000001}, // 0113
  {0x000000B1,0xFFE95917,0xB38E4396,0xB6A38DAB,0x755E1769,0x50285023,0xECA5E230,0xF9C69859,0x2D6E65C1,0x00000001}, // 0002
  {0x000000C6,0x46E7E19D,0x9CD65C85,0x75A3F6CB,0xBA18E29B,0x1F77477C,0xD9FA84CE,0x87BA709D,0x2FAC8DF9,0x00000001}, // 0101
  {0x000000E3,0xD686400B,0x7EFB2180,0x3EE49CA5,0x22781BD2,0x7B4B47B4,0x825948D2,0x40A720CD,0x30FA3E5A,0x00000001}, // 0000
  {0x00000085,0xEA3678CF,0x91DB0D2C,0x2B173813,0xFE0C0890,0x16C8602A,0x57338BBC,0xC4E2069C,0xEB8C5AA6,0x00000001}, // 0000
  {0x000000D6,0xBE71026E,0x348165EE,0x3B57B5DF,0x1168DBA0,0x0BF18EC7,0xF0C32238,0xDA6CC9F0,0x904CC0CF,0x00000001}, // 0002
  {0x0000005F,0x71AD1E37,0x82BC4D50,0xB2A8ED8C,0x1BEB8449,0x33FCDDD0,0x848CC2FB,0x6E9F4B55,0x33EFD7A4,0x00000001}, // 0000
  {0x00000011,0x4134BDB0,0x175A077F,0xBB5EE18B,0x1687C746,0x264376C7,0xC55B353C,0x46C85DBA,0x81B6AAF7,0x00000001}, // 0103
  {0x00000094,0x888FF8CB,0x282E6E5F,0x1D37F464,0x2D6B2681,0x30AC587E,0x528B2B55,0xD7DED977,0x7D292AE3,0x00000001}, // 0123
  {0x000000D9,0x48A2E6E4,0xCD610000,0xE466611A,0xC522F847,0xAFD164AB,0x7C43EA96,0x5E481177,0x1C4626AF,0x00000001}, // 0010 aggressive
  {0x000000E5,0x71448E83,0xD0860001,0xDBFDCC17,0x80745FC0,0x0AF2DA0B,0x504E9D69,0x1B0C9E16,0xF41C12F6,0x00000001}, // 0101 aggressive
  {0x0000003E,0xED6D9F85,0xA6D70002,0x7E6B93CB,0xD52234A4,0x266DDBB2,0x63F8CE52,0x118A3136,0xF0CBA60D,0x00000001}, // 0012 aggressive
  {0x00000025,0xD04F6B0E,0x16AD0003,0x5013A02F,0xB7D951BE,0x5D4ED559,0xA4982A6C,0xD5476083,0x2555C40E,0x00000001}, // 0123 aggressive
  {0x00000005,0x45C2E10D,0x273D0100,0x757CE4AC,0x1E2F7BB4,0xB314FB6C,0x11741D33,0x10508EF2,0x1A601C7D,0xFFFFFFFF}, // 0010 cmc only
  {0x00000056,0x30E19DF4,0x8C460101,0xBA5C933F,0xE650DD4F,0xA1B7D74E,0x1C4A2BE4,0x5C7888BE,0x36590A07,0xFFFFFFFF}, // 0111 cmc only
  {0x00000085,0x3B37FFD3,0x9F14B33B,0x30B66C24,0x3568B777,0x30E07B26,0x1033274C,0x79FA8716,0x2C68E3F4,0xFFFFFFFF}, // 0123 cmc only
  {0x00000080,0xB75263C5,0x41668D03,0xF6702E3D,0x27D05850,0x0AACF2F4,0x9B6A396C,0x77562F1D,0x933563A8,0xFFFFFFFF}, // 0113 cmc only
  {0x00000003,0x52A1DF42,0xD8A36271,0x4482012B,0x3261CB99,0xA748FFBA,0x68131ED1,0x9AA6F0DB,0x28E4E78A,0xFFFFFFFF}, // 0111 cmc only
  {0x00000087,0x23A58F8F,0xD59495C1,0x45074B81,0xC0B65A2B,0x834653C0,0x8696CB62,0x91DDCD8F,0x723F8B84,0xFFFFFFFF}, // 0101 cmc only
  {0x000000CC,0x9661BA34,0x7604002A,0x502B7490,0x00860AC2,0x5C388FF2,0x7EB10509,0x4DA0AE1C,0xD1C60CFB,0x00000001}, // 0012 dummy
  {0x00000021,0xE765D2F6,0xC61170A7,0x279E2821,0xE318702E,0x25FE9132,0x38D5F0DF,0xE9BE8686,0xE29AD459,0x00000000}  // 0113 no success
};
#endif

#ifdef HAVE_OGR_CORES
// OGR test cases
// [0] - expected number of nodes (~ if no solution expected to be found)
// [1] - number of marks
// [2..9] - first differences
//
// CAUTION : Tests should be sorted by number of marks to avoid unecessary
//           overhead.
static const s32 ogr_test_cases[TEST_CASE_COUNT][TEST_CASE_DATA] = {
  { 0x0009F217, 21,  2, 22, 32, 21,  5,  1},             // 01
  {~0x000561C9, 21,  1,  2,  4,  5,  8, 10},             // 02
  {~0x0038C35E, 21,  2, 22, 32,  1,  3, 10},             // 03
  {~0x00323B9A, 21,  9, 24,  4,  1, 59},                 // 04
  {~0x000EA7B9, 21,  5, 12, 11,  8, 16, 10, 44},         // 05
  { 0x0018818F, 22,  1,  8,  5, 29, 27, 36},             // 06
  {~0x0004B648, 22,  1,  2,  4,  5,  8, 10},             // 07
  {~0x0022CF3A, 22,  1,  8,  5, 29, 27, 37},             // 08
  {~0x0018B0BE, 22,  5, 12, 11,  8, 16, 10, 44},         // 09
  {~0x008CB937, 22,  9, 24,  4,  1, 59},                 // 10
  {~0x0061B8C0, 22,  3,  4, 10, 44,  5, 25},             // 11
  {~0x001AC0A0, 22,  2, 22, 32, 21,  5,  1},             // 12
  { 0x00093D71, 23,  3,  4, 10, 44,  5, 25},             // 13
  {~0x003B1EF7, 23,  1,  2,  4,  5,  8},                 // 14
  {~0x001A3C2B, 23,  3,  4, 10, 44,  5, 26},             // 15
  {~0x000A814D, 23,  5, 12, 11,  8, 16, 10, 44},         // 16
  {~0x0036E9CC, 23,  9, 24,  4,  1, 59},                 // 17
  {~0x0008B55C, 23,  2, 22, 32, 21,  5,  1},             // 18
  { 0x00165473, 24,  9, 24,  4,  1, 59, 25},             // 19
  {~0x00074037, 24,  1,  2,  4,  5,  8, 10, 14},         // 20
  {~0x0068CF0D, 24,  9, 24,  4,  1, 59, 26},             // 21
  {~0x001209D4, 24,  5, 12, 11,  8, 16, 10, 44, 30},     // 22
  {~0x000FA7EB, 24, 12, 17, 10, 33, 19, 55},             // 23
  {~0x004490DA, 24,  1,  8,  5, 29, 27, 36, 16},         // 24
  {~0x002DD344, 24,  2, 22, 32, 21,  5,  1, 12},         // 25
  { 0x0003B627, 25, 12, 17, 10, 33, 19, 55, 11},         // 26
  {~0x0030B179, 25,  1,  2,  4,  5,  8, 10, 14, 21},     // 27
  {~0x002F885A, 25,  2,  7, 22,  5, 14,  4, 64, 37},     // 28
  {~0x0043227A, 25,  2, 22, 32, 21,  5,  1, 12, 34},     // 29
  { 0x0046F7C0, 26,  5, 12, 11,  8, 16, 10, 44, 30},     // 30
  { 0x0090AD25, 27,  3, 12, 26, 25, 29,  2,  9, 36},     // 31
  {~0x00177314, 27,  8, 47, 19, 11,  2,  4,  1,  9}      // 32
};
#endif  /* HAVE_OGR_CORES */

#ifdef HAVE_OGR_PASS2
// OGR-P2 test cases
// [0] - expected number of nodes (~ if no solution expected to be found)
// [1] - number of marks
// [2] - Minimum starting position
// [3..9] - first differences
static const s32 ogrp2_test_cases[TEST_CASE_COUNT][TEST_CASE_DATA] = {
  // Test cases borrowed from the standard OGR test suite
  { 0x000D1B52, 21,  0,  2, 22, 32, 21,  5,  1},
  {~0x0057102A, 21,  0,  1,  2,  4,  5,  8, 10},
  {~0x0058E9DE, 21,  0,  2, 22, 32,  1,  3, 10},
  {~0x007D1FD7, 22,  0,  1,  2,  4,  5,  8, 10},
  { 0x0015ACEC, 22,  0,  1,  8,  5, 29, 27, 36},
  {~0x001BE4B3, 22,  0,  1,  8,  5, 29, 27, 37},
  {~0x00441720, 23,  0,  1,  2,  4,  5,  8, 10},
  { 0x000EFA83, 23,  0,  3,  4, 10, 44,  5, 25},
  {~0x0027C638, 23,  0,  3,  4, 10, 44,  5, 26},
  { 0x000ADD64, 24,  0,  9, 24,  4,  1, 59, 25},
  {~0x003C3A07, 24,  0,  9, 24,  4,  1, 59, 26},
  {~0x01298F41, 24,  0,  1,  2,  4,  5,  8, 10, 14},
  { 0x0018EE3D, 25,  0, 12, 17, 10, 33, 19, 55, 11},
  {~0x00BE2768, 25,  0, 12, 17, 10, 33, 19, 55, 23},
  // OGR-P2 specific test cases
  {~0x02F4CB08, 24, 134, 44, 22, 23},
  {~0x02E6C8AF, 24, 134, 50, 19, 14},
  {~0x02D42454, 24, 120, 11, 57,  7,  1},
  {~0x02961CEB, 24, 120, 31, 38,  3,  6},
  {~0x029EF7C8, 24, 120, 41, 22,  2,  9},
  {~0x021BC931, 24, 120, 52,  5, 11,  8},
  {~0x023053BC, 25, 146, 27, 75, 17},
  {~0x02EEF245, 25, 146, 24, 66, 33},
  {~0x0328B048, 25, 145, 47, 48, 19,  1},
 // Duplicates follow
  { 0x000D1B52, 21,  0,  2, 22, 32, 21,  5,  1},
  {~0x0057102A, 21,  0,  1,  2,  4,  5,  8, 10},
  {~0x0058E9DE, 21,  0,  2, 22, 32,  1,  3, 10},
  {~0x007D1FD7, 22,  0,  1,  2,  4,  5,  8, 10},
  { 0x0015ACEC, 22,  0,  1,  8,  5, 29, 27, 36},
  {~0x001BE4B3, 22,  0,  1,  8,  5, 29, 27, 37},
  {~0x02D42454, 24, 120, 11, 57,  7,  1},
  {~0x02961CEB, 24, 120, 31, 38,  3,  6},
  {~0x02EEF245, 25, 146, 24, 66, 33}
};
#endif  /* HAVE_OGR_PASS2 */


// PROJECT_NOT_HANDLED("add your test data here")

// ---------------------------------------------------------------------------

// returns 0 if not supported, <0 on failed or break
static long SelfTestInternal( unsigned int contest, int stress )
{
  int threadpos, threadcount = 1;
  long successes = 0L;
  const char *contname;
  int userbreak = 0;
  unsigned long runtime_sec, runtime_usec;

  if (CheckExitRequestTrigger())
    return 0;

  if (contest >= CONTEST_COUNT)
  {
    LogScreen("test::error. invalid contest %u\n", contest );
    return 0;
  }
  if (!IsProblemLoadPermitted(-1, contest)) /* also checks HAVE_xxx_CORES */
    return 0;

  contname = CliGetContestNameFromID( contest );
  for ( threadpos = 0; 
        !userbreak && successes >= 0L && threadpos < threadcount;
        threadpos++ )
  {
    char lastmsg[100];
    unsigned int testnum;

    ClientEventSyncPost( CLIEVENT_SELFTEST_STARTED, &contest, sizeof(contest) );
    successes = 0L;
    lastmsg[0] = '\0';

    runtime_sec = runtime_usec = 0;
    for ( testnum = 0 ; !userbreak && testnum < TEST_CASE_COUNT ; testnum++ )
    {
      const u32 (*test_cases)[TEST_CASE_COUNT][TEST_CASE_DATA] = NULL;
      u32 expectedsolution_hi, expectedsolution_mid, expectedsolution_lo;
      ContestWork contestwork;
      Problem *thisprob;

      memset(&contestwork, 0, sizeof(contestwork));
      expectedsolution_lo = expectedsolution_mid = expectedsolution_hi = 0; /* shaddup compiler */
#if defined(HAVE_RC5_72_CORES)
      if (contest == RC5_72)
      {
        test_cases = (const u32 (*)[TEST_CASE_COUNT][TEST_CASE_DATA])rc5_72_test_cases;
        expectedsolution_hi  = (*test_cases)[testnum][0];
        expectedsolution_mid = (*test_cases)[testnum][1];
        expectedsolution_lo  = (*test_cases)[testnum][2];
        contestwork.bigcrypto.key.hi  = expectedsolution_hi;
        contestwork.bigcrypto.key.mid = expectedsolution_mid;
        contestwork.bigcrypto.key.lo  = expectedsolution_lo & 0xFFFF0000L;
        if (testnum>1 && testnum<=7)
        {
          contestwork.bigcrypto.key.lo -= 0x00010000;
          if ((expectedsolution_lo & 0xFFFF0000L) == 0)
          {
            contestwork.bigcrypto.key.mid--;
            if (!~contestwork.bigcrypto.key.mid)
              contestwork.bigcrypto.key.hi--;
          }
        }
      }
#endif
#if defined(HAVE_OGR_CORES)
      if (contest == OGR_NG)
      {
        test_cases = (const u32 (*)[TEST_CASE_COUNT][TEST_CASE_DATA])ogr_test_cases;
        expectedsolution_lo = (*test_cases)[testnum][0];
      }
#endif
#if defined(HAVE_OGR_PASS2)
      if (contest == OGR_P2)
      {
        test_cases = (const u32 (*)[TEST_CASE_COUNT][TEST_CASE_DATA])ogrp2_test_cases;
        expectedsolution_lo = (*test_cases)[testnum][0];
      }
#endif
      //if (0)
      //{
      //  PROJECT_NOT_HANDLED(contest);
      //}

      switch (contest) 
      {
        #if defined(HAVE_CRYPTO_V2)
        case RC5_72:
        {
          contestwork.bigcrypto.iv.lo =  ( (*test_cases)[testnum][3] );
          contestwork.bigcrypto.iv.hi =  ( (*test_cases)[testnum][4] );
          contestwork.bigcrypto.plain.lo = ( (*test_cases)[testnum][5] );
          contestwork.bigcrypto.plain.hi = ( (*test_cases)[testnum][6] );
          contestwork.bigcrypto.cypher.lo = ( (*test_cases)[testnum][7] );
          contestwork.bigcrypto.cypher.hi = ( (*test_cases)[testnum][8] );
          contestwork.bigcrypto.keysdone.lo = ( 0 );
          contestwork.bigcrypto.keysdone.hi = ( 0 );
          contestwork.bigcrypto.iterations.lo = ( 0x00020000L ); // 17 bits instead of 16
          contestwork.bigcrypto.iterations.hi = ( 0 );
          contestwork.bigcrypto.randomsubspace = ( 0xFFFF ); // not defined (invalid)
          break;
        }
        #endif
        #if defined(HAVE_OGR_PASS2)
        case OGR_P2:
        {
          int tcd;
          contestwork.ogr_p2.workstub.stub.marks = (u16)((*test_cases)[testnum][1]);
          contestwork.ogr_p2.minpos              = (u32)((*test_cases)[testnum][2]);
          contestwork.ogr_p2.workstub.stub.length = 0;
          for (tcd = 0; tcd < TEST_CASE_DATA-3; tcd++) 
          {
            contestwork.ogr_p2.workstub.stub.diffs[tcd] = (u16)((*test_cases)[testnum][3+tcd]);
            if (contestwork.ogr_p2.workstub.stub.diffs[tcd] == 0)
              break;
            contestwork.ogr_p2.workstub.stub.length++;  
          }
          contestwork.ogr_p2.workstub.worklength = 0;
          contestwork.ogr_p2.nodes.lo = contestwork.ogr_p2.nodes.hi = 0;
          break;
        }  
        #endif
        #if defined(HAVE_OGR_CORES)
        case OGR_NG: 
        {
          int tcd;
          contestwork.ogr_ng.workstub.stub.marks = (u16)((*test_cases)[testnum][1]);
          contestwork.ogr_ng.workstub.stub.length = 0;
          for (tcd = 0; tcd < TEST_CASE_DATA-2; tcd++) 
          {
            contestwork.ogr_ng.workstub.stub.diffs[tcd] = (u16)((*test_cases)[testnum][2+tcd]);
            if (contestwork.ogr_ng.workstub.stub.diffs[tcd] == 0)
              break;
            contestwork.ogr_ng.workstub.stub.length++;  
          }
          contestwork.ogr_ng.workstub.worklength = 0;
          contestwork.ogr_ng.nodes.lo = contestwork.ogr_ng.nodes.hi = 0;
          contestwork.ogr_ng.workstub.collapsed = 0;
          break;
        }  
        #endif
        default:
          PROJECT_NOT_HANDLED(contest);
          userbreak = 1;
          break;
      } /* switch */

      if (userbreak)
        break;

      thisprob = ProblemAlloc();
      if (thisprob)
      {
        u32 tslice = 0x4000;
        u32 sec = 0;
        int non_preemptive_env = 0;
        int resultcode;

        #if (CLIENT_OS == OS_NETWARE)
        non_preemptive_env = (!nwCliIsPreemptiveEnv());
        if (non_preemptive_env)
          tslice = 2048;
        #elif (CLIENT_OS == OS_WIN16 || CLIENT_OS == OS_WIN32) || (CLIENT_OS == OS_WIN64) /* or win32s */
        non_preemptive_env = (winGetVersion() < 400);
        if (non_preemptive_env)
          tslice = 2048;
        #elif (CLIENT_OS == OS_RISCOS)
        non_preemptive_env = riscos_check_taskwindow();
        if (non_preemptive_env)
          tslice = 32768;
        #endif
        #if defined(HAVE_OGR_CORES)
        if (contest == OGR_NG && stress)
          tslice = 1;
        #endif

        if (ProblemLoadState( thisprob, &contestwork,
                              contest, tslice, 0, 0, 0, 0, NULL ) == 0)
        {
          ClientEventSyncPost( CLIEVENT_SELFTEST_TESTBEGIN, (void *)thisprob, -1 );
          do
          {
            if (non_preemptive_env)
            {
              #if (CLIENT_OS == OS_WIN16) || (CLIENT_OS == OS_WIN32) || (CLIENT_OS == OS_WIN64) /* or win32s */
              w32Yield(); /* pump waiting messages */
              #elif (CLIENT_OS == OS_RISCOS)
              riscos_upcall_6();
              #elif (CLIENT_OS == OS_NETWARE)
              ThreadSwitchLowPriority();
              #endif
            }

            if (CheckExitRequestTrigger())
            {
              userbreak = 1;
              break;
            }

            if (contest == OGR_P2 || contest == OGR_NG) {
              /* show /some/ activity (the time changes) */
              if (thisprob->pub_data.runtime_sec >= sec) {
                LogScreen("\r%s: Test %02d working...", contname, testnum + 1 );
                sec = thisprob->pub_data.runtime_sec + 1;
              }
            }
          } while ( ProblemRun(thisprob) == RESULT_WORKING );

          resultcode = RESULT_WORKING;
          if (!userbreak)
          {
            const char *resulttext = NULL;
            resultcode = ProblemRetrieveState( thisprob, &contestwork, NULL, 1, 0 );

            runtime_sec += thisprob->pub_data.runtime_sec;
            runtime_usec += thisprob->pub_data.runtime_usec;
            if (runtime_usec >= 1000000ul)
            {
              runtime_sec++;
              runtime_usec-=1000000ul;
            }

            switch (contest)
            {
              #ifdef HAVE_CRYPTO_V2
              case RC5_72:
              {
                int expected_cmc_count = (int)(*test_cases)[testnum][9];
                    // may be <= 0 if no solution, but perhaps some cmc key(s)
                if ( expected_cmc_count == 0 &&        /* expect no solution and no cmc */
                     ( resultcode != RESULT_NOTHING || 
                       contestwork.bigcrypto.check.count != 0 ) )
                {
                  contestwork.bigcrypto.key.lo  =
                  contestwork.bigcrypto.key.mid = contestwork.bigcrypto.key.hi = 0;
                  resulttext = "FAILED0";
                  resultcode = -1;
                }
                else if ( expected_cmc_count < 0 &&       /* expect no solution but cmc */
                          ( resultcode != RESULT_NOTHING || 
                            contestwork.bigcrypto.check.count != (u32)(-expected_cmc_count)) )
                {
                  //contestwork.bigcrypto.key.lo  =
                  //contestwork.bigcrypto.key.mid = contestwork.bigcrypto.key.hi = 0;
                  resulttext = "FAILED1";
                  resultcode = -1;
                }
                else if ( expected_cmc_count > 0 && resultcode != RESULT_FOUND )     /* no solution */
                {
                  contestwork.bigcrypto.key.lo  =
                  contestwork.bigcrypto.key.mid = contestwork.bigcrypto.key.hi = 0;
                  resulttext = "FAILED2";
                  resultcode = -1;
                }
                else if ( expected_cmc_count > 0 &&
                          ( contestwork.bigcrypto.key.hi  != expectedsolution_hi  ||
                            contestwork.bigcrypto.key.mid != expectedsolution_mid ||
                            contestwork.bigcrypto.key.lo  != expectedsolution_lo ) )
                {                                                  /* wrong solution */
                  resulttext = "FAILED3";
                  resultcode = -1;
                }
                else if ( expected_cmc_count > 0 && 
                          contestwork.bigcrypto.check.count != (u32)expected_cmc_count )
                {
                  resulttext = "FAILED4";
                  resultcode = -1;
                }
                else if ( expected_cmc_count != 0 &&
                          ( contestwork.bigcrypto.check.hi  != expectedsolution_hi  ||
                            contestwork.bigcrypto.check.mid != expectedsolution_mid ||
                            contestwork.bigcrypto.check.lo  != expectedsolution_lo ) )
                {                                          /* wrong partial solution */
                  resulttext = "FAILED5";
                  resultcode = -1;
                }
                else if ( expected_cmc_count <= 0 )         /* correct 'no' solution */
                {
                  expectedsolution_lo = contestwork.bigcrypto.key.lo;
                  resulttext = "passed";
                  successes++;
                }
                else                                             /* correct solution */
                {
                  resulttext = "passed";
                  successes++;
                }
                LogScreen( "\r%s: Test %02d %s: %02X:%08X:%08X-%02X:%08X:%08X\n",
                   contname, testnum + 1, resulttext, contestwork.bigcrypto.key.hi,
                   contestwork.bigcrypto.key.mid, contestwork.bigcrypto.key.lo,
                   expectedsolution_hi, expectedsolution_mid, expectedsolution_lo );
                break;
              }
              #endif
              #ifdef HAVE_OGR_PASS2
              case OGR_P2:
              {
                if (expectedsolution_lo & 0x80000000)  // no solution
                {
                  expectedsolution_lo = ~expectedsolution_lo;
                  if (resultcode != RESULT_NOTHING ||
                    contestwork.ogr_p2.nodes.lo != expectedsolution_lo)
                  {
                    resulttext = "FAILED";
                    resultcode = -1;
                  }
                  else
                  {
                    resulttext = "passed";
                    successes++;
                  }
                }
                else if (resultcode != RESULT_FOUND ||
                    contestwork.ogr_p2.nodes.lo != expectedsolution_lo)
                {
                  resulttext = "FAILED";
                  resultcode = -1;
                }
                else
                {
                  resulttext = "passed";
                  successes++;
                }
                LogScreen( "\r%s: Test %02d %s: %s %08X-%08X\n",
                                  contname, testnum + 1, resulttext,
                                  ogr_stubstr(&contestwork.ogr_p2.workstub.stub),
                                  contestwork.ogr_p2.nodes.lo, expectedsolution_lo );
                break;
              }
              #endif
              #ifdef HAVE_OGR_CORES
              case OGR_NG:
              {
                int logTo;

                resulttext = NULL; // assume success
                if (expectedsolution_lo & 0x80000000)  // no solution
                {
                  expectedsolution_lo = ~expectedsolution_lo;
                  if (resultcode != RESULT_NOTHING ||
                    contestwork.ogr_ng.nodes.lo != expectedsolution_lo)
                  {
                    resulttext = "FAILED1";
                  }
                }
                else if (resultcode != RESULT_FOUND ||
                    contestwork.ogr_ng.nodes.lo != expectedsolution_lo)
                {
                  resulttext = "FAILED2";
                }

                if (resulttext == NULL)
                {
                  resulttext = "passed ";
                  successes++;
                  logTo = LOGTO_SCREEN;  /* same as LogScreen() */
                }
                else
                {
                  resultcode = -1;
                  logTo = LOGTO_SCREEN|LOGTO_FILE|LOGTO_MAIL; /* same as Log() */
                }

                LogTo( logTo, "\r%s: Test %02d %s: %s %08X-%08X\n",
                                     contname, testnum + 1, resulttext,
                                     ogrng_stubstr(&contestwork.ogr_ng.workstub),
                                     contestwork.ogr_ng.nodes.lo, expectedsolution_lo );
                break;
              }
              #endif
              default:
              {
                PROJECT_NOT_HANDLED(contest);
                break;
              }
            } /* switch */

          } /* if (!userbreak) */

          ClientEventSyncPost( CLIEVENT_SELFTEST_TESTEND, &resultcode, sizeof(resultcode) );
        } /* if load state ok */
        else {
          LogScreen( "\r%s: Test %02d load failed\n", contname, testnum + 1);
        }
        ProblemFree(thisprob);
      } /* if ProblemAlloc() */
      #ifdef HAVE_OGR_CORES
      if (contest == OGR_NG) {
        // Release cached limits once they are no longer required. We assume the
        // tests are sorted by number of marks.
        if (testnum == TEST_CASE_COUNT - 1 || (*test_cases)[testnum][1] != (*test_cases)[testnum+1][1]) {
          ogr_cleanup_cache();
        }
      }
      #endif
    } /* for ( testnum = 0 ; testnum < TEST_CASE_COUNT ; testnum++ ) */

    if (userbreak)
      successes = -1L;
    else  
    {
      if (successes > 0L)
      {
        Log( "%s: %ld/%ld Tests Passed (%lu.%06lu seconds)\n", contname,
           successes, (long) TEST_CASE_COUNT, runtime_sec, runtime_usec );
      }
      if (successes != ((long)TEST_CASE_COUNT))
      {
        Log( "%s: WARNING WARNING WARNING: %ld Tests FAILED!!!\n", 
          contname, (((long)TEST_CASE_COUNT) - successes) );
        successes = -1L;
      }
    }
    ClientEventSyncPost( CLIEVENT_SELFTEST_FINISHED, &successes, sizeof(successes) );

  } /* for ( threadpos = 0; threadpos < threadcount; threadpos++ ) */

  return (successes);
}

long SelfTest( unsigned int contest )
{
  return SelfTestInternal(contest, 0);
}

long StressTest(unsigned int contest)
{
  switch (contest) {
    #if defined(HAVE_RC5_72_CORES)
    case RC5_72: return StressRC5_72();
    #endif
    #if defined(HAVE_OGR_CORES)
    case OGR_NG: return SelfTestInternal(contest, 1);
    #endif
    default: return SelfTest(contest);
  }
}
