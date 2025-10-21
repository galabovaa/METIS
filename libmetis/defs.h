/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * defs.h
 *
 * This file contains constant definitions
 *
 * Started 8/27/94
 * George
 *
 * $Id: defs.h 13933 2013-03-29 22:20:46Z karypis $
 *
 */

#ifndef _LIBMETIS_DEFS_H_
#define _LIBMETIS_DEFS_H_

#define METISTITLE              "METIS 5.0 Copyright 1998-13, Regents of the University of Minnesota\n"

#define HTLENGTH		((1<<11)-1)

#define INIT_MAXNAD             200     /* Initial number of maximum number of 
                                           adjacent domains. This number will be
                                           adjusted as required. */

#define UNMATCHED		-1

#define LARGENIPARTS		7	/* Number of random initial partitions */

#define COARSEN_FRACTION	0.85	/* Node reduction between succesive coarsening levels */

#define COMPRESSION_FRACTION		0.85

#define MMDSWITCH		        120

/* Default ufactors for the various operational modes */
#define PMETIS_DEFAULT_UFACTOR          1
#define MCPMETIS_DEFAULT_UFACTOR        10
#define KMETIS_DEFAULT_UFACTOR          30
#define OMETIS_DEFAULT_UFACTOR          200

#endif
