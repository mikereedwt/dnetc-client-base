/*
 * Copyright distributed.net 1999-2008 - All Rights Reserved
 * For use in distributed.net projects only.
 * Any other distribution or use of this source violates copyright.
 *
*/
#ifndef __OGR_INTERFACE_H__
#define __OGR_INTERFACE_H__ "@(#)$Id: ogr-interface.h,v 1.1 2008/02/10 00:07:41 kakace Exp $"

#include <limits.h>

#if (UINT_MAX < 0xfffffffful)
  #error "ogr needs an int that's not less than 32bits"
#elif (UINT_MAX == 0xffffffff)
  #define OGR_INT_SIZE 4
#elif (UINT_MAX == 0xffffffffffffffff)
  #define OGR_INT_SIZE 8
#else
  #error "What's up Doc?"
#endif

#include "cputypes.h"


/* ===================================================================== */

/*
 * Constants for return values from all the below functions.
 * Those starting with CORE_S are success codes, and those starting
 * with CORE_E are error codes.
 */
#define CORE_S_OK       0
#define CORE_S_CONTINUE 1
#define CORE_S_SUCCESS  2
#define CORE_E_MEMORY   (-1)
#define CORE_E_STUB     (-2)
#define CORE_E_FORMAT   (-3)
#define CORE_E_INTERNAL (-4)

#ifndef __SUNPRO_CC
  #include "pack1.h"
#else
  #undef DNETC_PACKED
  #define DNETC_PACKED
#endif
/*
 * Dispatch table structure. A pointer to one of these should be returned
 * from an exported function in the module.
 *
 * The result callback is weird, it implies that only one client in the
 * entire process will use this core (but that client can have multiple
 * threads). Oh well.
 */
typedef struct {
  /*
   * Initialize the core, called once for all threads.
   * CAUTION : Never allocate resources here because there's no mean to
   *     deallocate them later.
   */
  int (*init)(void);

  /*
   * Create a new work unit, called once for each thread.
   * The format of input is defined by the core.
   */
  int (*create)(void *input, int inputlen, void *state, int statelen, int extra);

  /*
   * Continue working, return CORE_S_OK if no more work to do, or
   * CORE_S_CONTINUE if things need to keep going.
   * On input, nodes should contain the number of algorithm iterations
   * to do. On output, nodes will contain the actual number of iterations
   * done.
   *
   * If with_time_constraints is 0, the OGR cruncher uses the nodeslimit 
   * merely as a hint when to leave the cruncher rather than adhering to it 
   * exactly. There is a slight speed increase (negligible in a preemptive 
   * non-realtime environment) when applying the hint scheme, but cannot 
   * be used in a cruncher that is bound by time constraints (eg 
   * non-preemptive or real-time environments) because it can happen 
   * that a nodeslimit request of 1000 will end up with 32000 nodes done.
  */
  int (*cycle)(void *state, int *steps, int with_time_constraints);

  /*
   * If cycle returns CORE_S_SUCCESS, call getresult to get the successful
   * result. If called at other times, returns the current state of the 
   * search.
   */
  int (*getresult)(void *state, void *result, int resultlen);

  /*
   * Clean up state structure.
   */
  int (*destroy)(void *state);

  /*
   * Clean up anything allocated in init().
   * FIXME : It turns out this function is never called !
   */
  int (*cleanup)(void);

  /*
   * Get value of cached nodes (node_offset field) - offset of this field
   * in state structure is different for 32- and 64-bit OGR.
   */
  int (*getnodeoffset)(void *state);

} DNETC_PACKED CoreDispatchTable;

/* ===================================================================== */

/* specifies the number of ruler diffs can be represented.
** Warning: increasing this will cause all structures based
** on workunit_t in packets.h to change, possibly breaking
** network and buffer structure operations.
*/
#define STUB_MAX 10

struct Stub {           /* size is 24 */
  u16 marks;            /* N-mark ruler to which this stub applies */
  u16 length;           /* number of valid elements in the stub[] array */
  u16 diffs[STUB_MAX];  /* first <length> differences in ruler */
} DNETC_PACKED;

struct WorkStub {       /* size is 28 */
  struct Stub stub;     /* stub we're working on */
  u32 worklength;       /* depth of current state */
} DNETC_PACKED;

#ifndef __SUNPRO_CC
  #include "pack0.h"
#else
  #undef DNETC_PACKED
#endif


#define OGR_MAXDEPTH 30


#if defined(OGROPT_OGR_CYCLE_ALTIVEC) && (defined(__VEC__) || defined (__ALTIVEC__))
   /* Vector (PPC/AltiVec) implementation
   ** Since ogr.cpp (thus ogr.h) is included from ppc/ogr-vec.cpp, we can rely
   ** upon OGROPT_OGR_CYCLE_ALTIVEC to enable vector declarations.
   ** VECTOR is defined in ppc/ogr-vec.cpp
   */
   typedef union {
      vector unsigned int v;
      unsigned int u[4];
   } VECTOR;
#endif


/*
** ogr_sup.cpp
*/
unsigned long ogr_nodecount(const struct Stub *);
const char *ogr_stubstr_r(const struct Stub *stub, char *buffer,
                          unsigned int bufflen, int worklength);
const char *ogr_stubstr(const struct Stub *stub);

#endif /* __OGR_INTERFACE_H__ */

