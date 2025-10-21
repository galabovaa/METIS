/*!
\file  error.c
\brief Various error-handling functions

This file contains functions dealing with error reporting and termination

\author George
\date 1/1/2007
\version\verbatim $Id: error.c 10711 2011-08-31 22:23:04Z karypis $ \endverbatim
*/


#define _GK_ERROR_C_  /* this is needed to properly declare the gk_jub* variables
                         as an extern function in GKlib.h */

#include <GKlib.h>

/*************************************************************************/
/*! This function prints an error message and raises a signum signal
 */
/*************************************************************************/
void gk_errexit(int signum, char *f_str,...)
{
  va_list argp;

  va_start(argp, f_str);
  vfprintf(stderr, f_str, argp);
  va_end(argp);

  fprintf(stderr,"\n");
  fflush(stderr);

  raise(signum);
}
