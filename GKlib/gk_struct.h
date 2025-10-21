/*!
\file gk_struct.h
\brief This file contains various datastructures used/provided by GKlib

\date   Started 3/27/2007
\author George
\version\verbatim $Id: gk_struct.h 13005 2012-10-23 22:34:36Z karypis $ \endverbatim
*/

#ifndef _GK_STRUCT_H_
#define _GK_STRUCT_H_


/********************************************************************/
/*! Generator for gk_??KeyVal_t data structure */
/********************************************************************/
#define GK_MKKEYVALUE_T(NAME, KEYTYPE, VALTYPE) \
typedef struct {\
  KEYTYPE key;\
  VALTYPE val;\
} NAME;\



/********************************************************************/
/*! Generator for gk_?pq_t data structure */
/********************************************************************/
#define GK_MKPQUEUE_T(NAME, KVTYPE)\
typedef struct {\
  gk_idx_t nnodes;\
  gk_idx_t maxnodes;\
\
  /* Heap version of the data structure */ \
  KVTYPE   *heap;\
  gk_idx_t *locator;\
} NAME;\

/*************************************************************************/
/*! The following data structure stores information about a memory 
    allocation operation that can either be served from gk_mcore_t or by
    a gk_malloc if not sufficient workspace memory is available. */
/*************************************************************************/
typedef struct gk_mop_t {
  int type;
  ssize_t nbytes;
  void *ptr;
} gk_mop_t;


/*************************************************************************/
/*! The following structure stores information used by Metis */
/*************************************************************************/
typedef struct gk_mcore_t {
  /* Workspace information */
  size_t coresize;     /*!< The amount of core memory that has been allocated */
  size_t corecpos;     /*!< Index of the first free location in core */
  void *core;	       /*!< Pointer to the core itself */

  /* These are for implementing a stack-based allocation scheme using both
     core and also dynamically allocated memory */
  size_t nmops;         /*!< The number of maop_t entries that have been allocated */
  size_t cmop;          /*!< Index of the first free location in maops */
  gk_mop_t *mops;       /*!< The array recording the maop_t operations */
} gk_mcore_t;



#endif
