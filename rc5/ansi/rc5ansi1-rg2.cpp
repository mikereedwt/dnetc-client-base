// Copyright distributed.net 1997-2002 - All Rights Reserved
// For use in distributed.net projects only.
// Any other distribution or use of this source violates copyright.

// dual-key, mixed round 3 and encryption, A1/A2 use for last value,
// non-arrayed S1/S2 tables, direct use of last value, run-time
// generation of S0[]

// $Log: rc5ansi1-rg2.cpp,v $
// Revision 1.7  2002/09/02 00:35:55  andreasb
// sync: merged changes from release-2-7111 branch between
//       2000-07-11 and release-2-7111_20020901 into trunk
//
// Revision 1.6.2.1  2002/04/12 23:56:56  andreasb
// 2002 copyright update - round 2
//
// Revision 1.6  1998/07/08 22:59:44  remi
// Lots of $Id: rc5ansi1-rg2.cpp,v 1.7 2002/09/02 00:35:55 andreasb Exp $ stuff.
//
// Revision 1.5  1998/06/14 08:27:28  friedbait
// 'Id' tags added in order to support 'ident' command to display a bill of
// material of the binary executable
//
// Revision 1.4  1998/06/14 08:13:45  friedbait
// 'Log' keywords added to maintain automatic change history
//
//


/*  This file is included from rc5.cpp so we can use __inline__.  */

//
//*Use the last value each time instead of A1
//
//*run-time generation of S0[] :
//
//	- loading a large constant on RISC need two instructions.
//	  (ie, on sparc :)
//		sethi %hi(1444465436),%g2
//		or %g2,%lo(1444465436),%g2
//
//	- generating S0[] at run time need only one instruction
//	  since S0[n] = S0[n-1] + Q
//	  (ie, : currentS0 += Q )
//
//	- drawback : we need two more registers
//	  one for 'currentS0' and one for 'Q'
//
//	- strange thing : on MIPS, gcc seems to 'optimize' a bit too much,
//	  it drops cS0 and Q, and load constants anyway ... (grrr)
//
//*The main crypt routine needs :
//
//	- 26 registers for S00..S25
//
//	- 3 registers for A1,Llo1,Lhi1
//
//	- 2 registers for cS0 and Q
//	- 2 registers for eA1 and eB1
//	 note that they should overlap with cS0 and Q
//	 since the firsts are only used in round 1
//	 and the lasts are only used in round 3
//
//	- 1 more register for ROTL (Llo1 + A1 + Lhi1, A1 + Lhi1),
//	  since a decent compiler should do :
//		tmp = A1+Lhi1
//		Llo1 += tmp
//		Llo1 = ROTL (Llo1, tmp)
//	  (this assumes we have a rotate instruction)
//
// So we need 26+3+2+1 = 31 registers
//
// On MIPS, HP-PA and PowerPC, it could be a gain to  use S00..S25 instead of 'A1',
// since we will need 30 registers and these chips have 32 registers.
// (don't know if we really could use 30 registers in a function, since I can't get
//  this @%! cross-gcc to compile !)
//
// On Sparc we are short of registers.
//
// R�mi Guyomarch - 97/07/19

#if (!defined(lint) && defined(__showids__))
const char *rc5ansi1_rg2_cpp (void) {
return "@(#)$Id: rc5ansi1-rg2.cpp,v 1.7 2002/09/02 00:35:55 andreasb Exp $"; }
#endif

#include "problem.h"
#include "rotate.h"


#if (PIPELINE_COUNT != 1)
#error "Expecting pipeline count of 1"
#endif

#ifndef _CPU_32BIT_
#error "everything assumes a 32bit CPU..."
#endif


#define _P_RC5	 0xB7E15163
#define _Q	 0x9E3779B9
#define S_not(n) (_P_RC5+_Q*n)


// Round 1 macros
// --------------
#define ROUND1EVEN(S1N,S1prev)		\
cS0 += Q;				\
S1N = ROTL3 (S1prev + Lhi1 + cS0);	\
Llo1 = ROTL (Llo1 + S1N + Lhi1, S1N + Lhi1);

#define  ROUND1ODD(S1N,S1prev)		\
cS0 += Q;				\
S1N = ROTL3 (S1prev + Llo1 + cS0);	\
Lhi1 = ROTL (Lhi1 + S1N + Llo1, S1N + Llo1);

// Round 2 macros
// --------------
#define ROUND2EVEN(S1N,S1prev)		\
S1N = ROTL3 (S1prev + Lhi1 + S1N);	\
Llo1 = ROTL (Llo1 + S1N + Lhi1, S1N + Lhi1);

#define  ROUND2ODD(S1N,S1prev)		\
S1N = ROTL3 (S1prev + Llo1 + S1N);	\
Lhi1 = ROTL (Lhi1 + S1N + Llo1, S1N + Llo1);

// Round 3 macros
// --------------
#define ROUND3EVEN(S1N)				\
A1 = ROTL3 (A1 + Lhi1 + S1N);			\
eA1 = ROTL (eA1 ^ eB1, eB1) + A1;		\
Llo1 = ROTL (Llo1 + A1 + Lhi1, A1 + Lhi1);

#define ROUND3ODD(S1N)				\
A1 = ROTL3 (A1 + Llo1 + S1N);			\
eB1 = ROTL (eA1 ^ eB1, eA1) + A1;		\
Lhi1 = ROTL (Lhi1 + A1 + Llo1, A1 + Llo1);

// rc5_unit will get passed an RC5WorkUnit to complete
// this is where all the actually work occurs, this is where you optimize.
// assembly gurus encouraged.
// Returns: 0 - nothing found, 1 - found on pipeline 1,
//   2 - found pipeline 2, 3 - ... etc ...

static __inline__
u32 rc5_unit_func( RC5UnitWork * rc5unitwork )
{
  u32 S1_00,S1_01,S1_02,S1_03,S1_04,S1_05,S1_06,S1_07,S1_08,S1_09,
      S1_10,S1_11,S1_12,S1_13,S1_14,S1_15,S1_16,S1_17,S1_18,S1_19,
      S1_20,S1_21,S1_22,S1_23,S1_24,S1_25;

  register u32 Llo1, Lhi1;

  Llo1 = rc5unitwork->L0.lo;
  Lhi1 = rc5unitwork->L0.hi;

  { register u32 cS0, Q;

    /* Begin round 1 of key expansion */

    /*  Special case while A and B are known to be zero.  */
    cS0 = _P_RC5;
    Q   = _Q;
    S1_00 = ROTL3(cS0);
    Llo1 = ROTL(Llo1 + S1_00, S1_00);

    ROUND1ODD  (S1_01,S1_00);
    ROUND1EVEN (S1_02,S1_01);
    ROUND1ODD  (S1_03,S1_02);
    ROUND1EVEN (S1_04,S1_03);
    ROUND1ODD  (S1_05,S1_04);
    ROUND1EVEN (S1_06,S1_05);
    ROUND1ODD  (S1_07,S1_06);
    ROUND1EVEN (S1_08,S1_07);
    ROUND1ODD  (S1_09,S1_08);
    ROUND1EVEN (S1_10,S1_09);
    ROUND1ODD  (S1_11,S1_10);
    ROUND1EVEN (S1_12,S1_11);
    ROUND1ODD  (S1_13,S1_12);
    ROUND1EVEN (S1_14,S1_13);
    ROUND1ODD  (S1_15,S1_14);
    ROUND1EVEN (S1_16,S1_15);
    ROUND1ODD  (S1_17,S1_16);
    ROUND1EVEN (S1_18,S1_17);
    ROUND1ODD  (S1_19,S1_18);
    ROUND1EVEN (S1_20,S1_19);
    ROUND1ODD  (S1_21,S1_20);
    ROUND1EVEN (S1_22,S1_21);
    ROUND1ODD  (S1_23,S1_22);
    ROUND1EVEN (S1_24,S1_23);
    ROUND1ODD  (S1_25,S1_24);
  }

  /* Begin round 2 of key expansion */

  ROUND2EVEN (S1_00,S1_25);
  ROUND2ODD  (S1_01,S1_00);
  ROUND2EVEN (S1_02,S1_01);
  ROUND2ODD  (S1_03,S1_02);
  ROUND2EVEN (S1_04,S1_03);
  ROUND2ODD  (S1_05,S1_04);
  ROUND2EVEN (S1_06,S1_05);
  ROUND2ODD  (S1_07,S1_06);
  ROUND2EVEN (S1_08,S1_07);
  ROUND2ODD  (S1_09,S1_08);
  ROUND2EVEN (S1_10,S1_09);
  ROUND2ODD  (S1_11,S1_10);
  ROUND2EVEN (S1_12,S1_11);
  ROUND2ODD  (S1_13,S1_12);
  ROUND2EVEN (S1_14,S1_13);
  ROUND2ODD  (S1_15,S1_14);
  ROUND2EVEN (S1_16,S1_15);
  ROUND2ODD  (S1_17,S1_16);
  ROUND2EVEN (S1_18,S1_17);
  ROUND2ODD  (S1_19,S1_18);
  ROUND2EVEN (S1_20,S1_19);
  ROUND2ODD  (S1_21,S1_20);
  ROUND2EVEN (S1_22,S1_21);
  ROUND2ODD  (S1_23,S1_22);
  ROUND2EVEN (S1_24,S1_23);
  ROUND2ODD  (S1_25,S1_24);

    /* Begin round 3 of key expansion (and encryption round) */

  { register u32 A1, eA1, eB1;

    eA1 = rc5unitwork->plain.lo + (A1 = ROTL3(S1_00 + S1_25 + Lhi1));
    Llo1 = ROTL(Llo1 + A1 + Lhi1, A1 + Lhi1);
    eB1 = rc5unitwork->plain.hi + (A1 = ROTL3(S1_01 + A1 + Llo1));
    Lhi1 = ROTL(Lhi1 + A1 + Llo1, A1 + Llo1);

    ROUND3EVEN (S1_02);
    ROUND3ODD  (S1_03);
    ROUND3EVEN (S1_04);
    ROUND3ODD  (S1_05);
    ROUND3EVEN (S1_06);
    ROUND3ODD  (S1_07);
    ROUND3EVEN (S1_08);
    ROUND3ODD  (S1_09);
    ROUND3EVEN (S1_10);
    ROUND3ODD  (S1_11);
    ROUND3EVEN (S1_12);
    ROUND3ODD  (S1_13);
    ROUND3EVEN (S1_14);
    ROUND3ODD  (S1_15);
    ROUND3EVEN (S1_16);
    ROUND3ODD  (S1_17);
    ROUND3EVEN (S1_18);
    ROUND3ODD  (S1_19);
    ROUND3EVEN (S1_20);
    ROUND3ODD  (S1_21);
    ROUND3EVEN (S1_22);
    ROUND3ODD  (S1_23);
	
    eA1 = ROTL(eA1 ^ eB1, eB1) + (A1 = ROTL3(S1_24 + A1 + Lhi1));
	
    if (rc5unitwork->cypher.lo == eA1 &&
	    rc5unitwork->cypher.hi == ROTL(eB1 ^ eA1, eA1) +
	      ROTL3(S1_25 + A1 + ROTL(Llo1 + A1 + Lhi1, A1 + Lhi1))) return 1;
	  return 0;	
  }
}


