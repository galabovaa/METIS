/*!
\file gk_defs.h
\brief This file contains various constants definitions

\date   Started 3/27/2007
\author George
\version\verbatim $Id: gk_defs.h 12732 2012-09-24 20:54:50Z karypis $ \endverbatim
*/

#ifndef _GK_DEFS_H_
#define _GK_DEFS_H_


#define LTERM                   (void **) 0     /* List terminator for GKfree() */

/* mopt_t types */
#define GK_MOPT_MARK            1
#define GK_MOPT_CORE            2
#define GK_MOPT_HEAP            3

/* GKlib signals to standard signal mapping */
#define SIGMEM  SIGABRT
#define SIGERR  SIGTERM

#endif
