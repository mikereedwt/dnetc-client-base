/* Hey, Emacs, this a -*-C++-*- file !
 *
 * Copyright distributed.net 1997-1999 - All Rights Reserved
 * For use in distributed.net projects only.
 * Any other distribution or use of this source violates copyright.
*/ 
#ifndef __DISPHELP_H__
#define __DISPHELP_H__ "@(#)$Id: disphelp.h,v 1.2.2.1 1999/04/13 19:45:23 jlawson Exp $"

/*
  full-screen, interactive (except for unix-ish platforms) help for 
  an invalid option (argv[x]). 'unrecognized_option' may be NULL or "\0"
*/
void DisplayHelp( const char * unrecognized_option );

#endif /* __DISPHELP_H__ */
