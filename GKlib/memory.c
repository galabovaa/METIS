/*!
\file  memory.c
\brief This file contains various allocation routines 

The allocation routines included are for 1D and 2D arrays of the 
most datatypes that GKlib support. Many of these routines are 
defined with the help of the macros in gk_memory.h. These macros 
can be used to define other memory allocation routines.

\date   Started 4/3/2007
\author George
\version\verbatim $Id: memory.c 10783 2011-09-21 23:19:56Z karypis $ \endverbatim
*/


#include <GKlib.h>

/* This is for the global mcore that tracks all heap allocations */
static __thread gk_mcore_t *gkmcore = NULL;


/*************************************************************************/
/*! Define the set of memory allocation routines for each data type */
/**************************************************************************/
GK_MKALLOC(gk_idx, gk_idx_t)


/*************************************************************************/
/*! This function initializes tracking of heap allocations. 
*/
/*************************************************************************/
int gk_malloc_init()
{
  if (gkmcore == NULL)
    gkmcore = gk_gkmcoreCreate();

  if (gkmcore == NULL)
    return 0;

  gk_gkmcorePush(gkmcore);

  return 1;
}


/*************************************************************************/
/*! This function frees the memory that has been allocated since the
    last call to gk_malloc_init().
*/
/*************************************************************************/
void gk_malloc_cleanup(int showstats)
{
  if (gkmcore != NULL) {
    gk_gkmcorePop(gkmcore);
    if (gkmcore->cmop == 0) {
      gk_gkmcoreDestroy(&gkmcore, showstats);
      gkmcore = NULL;
    }
  }
}


/*************************************************************************/
/*! This function is my wrapper around malloc that provides the following
    enhancements over malloc:
    * It always allocates one byte of memory, even if 0 bytes are requested.
      This is to ensure that checks of returned values do not lead to NULL
      due to 0 bytes requested.
    * It zeros-out the memory that is allocated. This is for a quick init
      of the underlying datastructures.
*/
/**************************************************************************/
void *gk_malloc(size_t nbytes, char *msg)
{
  void *ptr=NULL;

  if (nbytes == 0)
    nbytes++;  /* Force mallocs to actually allocate some memory */

  ptr = (void *)malloc(nbytes);

  if (ptr == NULL) {
    return NULL;
  }

  /* add this memory allocation */
  if (gkmcore != NULL) gk_gkmcoreAdd(gkmcore, GK_MOPT_HEAP, nbytes, ptr);

  /* zero-out the allocated space */
#ifndef NDEBUG
  memset(ptr, 0, nbytes);
#endif

  return ptr;
}


/*************************************************************************
* This function is my wrapper around realloc
**************************************************************************/
void *gk_realloc(void *oldptr, size_t nbytes, char *msg)
{
  void *ptr=NULL;

  if (nbytes == 0)
    nbytes++;  /* Force mallocs to actually allocate some memory */

  /* remove this memory de-allocation */
  if (gkmcore != NULL && oldptr != NULL) gk_gkmcoreDel(gkmcore, oldptr);

  ptr = (void *)realloc(oldptr, nbytes);

  if (ptr == NULL) {
    return NULL;
  }

  /* add this memory allocation */
  if (gkmcore != NULL) gk_gkmcoreAdd(gkmcore, GK_MOPT_HEAP, nbytes, ptr);

  return ptr;
}


/*************************************************************************
* This function is my wrapper around free, allows multiple pointers    
**************************************************************************/
void gk_free(void **ptr1,...)
{
  va_list plist;
  void **ptr;

  if (*ptr1 != NULL) {
    free(*ptr1);

    /* remove this memory de-allocation */
    if (gkmcore != NULL) gk_gkmcoreDel(gkmcore, *ptr1);
  }
  *ptr1 = NULL;

  va_start(plist, ptr1);
  while ((ptr = va_arg(plist, void **)) != LTERM) {
    if (*ptr != NULL) {
      free(*ptr);

      /* remove this memory de-allocation */
      if (gkmcore != NULL) gk_gkmcoreDel(gkmcore, *ptr);
    }
    *ptr = NULL;
  }
  va_end(plist);
}          
