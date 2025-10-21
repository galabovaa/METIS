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

/*************************************************************************
* This function is my wrapper around free, allows multiple pointers    
**************************************************************************/
void gk_free(void **ptr1)
{
  free(*ptr1);
  *ptr1 = NULL;
}          
