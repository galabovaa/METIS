/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * Frename.c
 * 
 * THis file contains some renaming routines to deal with different Fortran compilers
 *
 * Started 9/15/97
 * George
 *
 */


#include "metislib.h"

#define FRENAME(name, dargs, cargs, name1, name2, name3, name4)   \
  int name1 dargs { return name cargs; }                          \
  int name2 dargs { return name cargs; }                          \
  int name3 dargs { return name cargs; }                          \
  int name4 dargs { return name cargs; }


FRENAME(
    METIS_PartGraphRecursive_ts, 
    (idx_t *nvtxs, idx_t *ncon, idx_t *xadj, idx_t *adjncy, idx_t *vwgt, 
     idx_t *vsize, idx_t *adjwgt, idx_t *nparts, real_t *tpwgts, 
     real_t *ubvec, idx_t *options, idx_t *edgecut, idx_t *part, unsigned* rng_state),
    (nvtxs, ncon, xadj, adjncy, vwgt, 
     vsize, adjwgt, nparts, tpwgts, 
     ubvec, options, edgecut, part, rng_state),
    METIS_PARTGRAPHRECURSIVE_TS, 
    metis_partgraphrecursive_ts, 
    metis_partgraphrecursive_ts_, 
    metis_partgraphrecursive_ts__
) 
    

FRENAME(
    METIS_PartGraphKway_ts,
    (idx_t *nvtxs, idx_t *ncon, idx_t *xadj, idx_t *adjncy, idx_t *vwgt, 
     idx_t *vsize, idx_t *adjwgt, idx_t *nparts, real_t *tpwgts, 
     real_t *ubvec, idx_t *options, idx_t *edgecut, idx_t *part, unsigned* rng_state),
    (nvtxs, ncon, xadj, adjncy, vwgt, 
     vsize, adjwgt, nparts, tpwgts, 
     ubvec, options, edgecut, part, rng_state),
    METIS_PARTGRAPHKWAY_TS,
    metis_partgraphkway_ts,
    metis_partgraphkway_ts_,
    metis_partgraphkway_ts__
)

FRENAME(
  METIS_MeshToDual,
  (idx_t *ne, idx_t *nn, idx_t *eptr, idx_t *eind, idx_t *ncommon, idx_t *numflag, 
   idx_t **r_xadj, idx_t **r_adjncy),
  (ne, nn, eptr, eind, ncommon, numflag, r_xadj, r_adjncy),
  METIS_MESHTODUAL,
  metis_meshtodual,
  metis_meshtodual_,
  metis_meshtodual__
)


FRENAME(
  METIS_MeshToNodal,
  (idx_t *ne, idx_t *nn, idx_t *eptr, idx_t *eind, idx_t *numflag, idx_t **r_xadj, 
   idx_t **r_adjncy),
  (ne, nn, eptr, eind, numflag, r_xadj, r_adjncy),
  METIS_MESHTONODAL,
  metis_meshtonodal,
  metis_meshtonodal_,
  metis_meshtonodal__
)
  

FRENAME(
  METIS_PartMeshNodal_ts,
  (idx_t *ne, idx_t *nn, idx_t *eptr, idx_t *eind, idx_t *vwgt, idx_t *vsize, 
   idx_t *nparts, real_t *tpwgts, idx_t *options, idx_t *objval, idx_t *epart, 
   idx_t *npart, unsigned* rng_state),
  (ne, nn, eptr, eind, vwgt, vsize, nparts, tpwgts, options, objval, epart, npart, rng_state),
  METIS_PARTMESHNODAL_TS,
  metis_partmeshnodal_ts,
  metis_partmeshnodal_ts_,
  metis_partmeshnodal_ts__
)


FRENAME(
  METIS_PartMeshDual_ts,
  (idx_t *ne, idx_t *nn, idx_t *eptr, idx_t *eind, idx_t *vwgt, idx_t *vsize, 
   idx_t *ncommon, idx_t *nparts, real_t *tpwgts, idx_t *options, idx_t *objval, 
   idx_t *epart, idx_t *npart, unsigned* rng_state),
  (ne, nn, eptr, eind, vwgt, vsize, ncommon, nparts, tpwgts, options, objval, epart, npart, rng_state),
  METIS_PARTMESHDUAL_TS,
  metis_partmeshdual_ts,
  metis_partmeshdual_ts_,
  metis_partmeshdual_ts__
)


FRENAME(
  METIS_NodeND_ts,
  (idx_t *nvtxs, idx_t *xadj, idx_t *adjncy, idx_t *vwgt, idx_t *options, idx_t *perm, 
   idx_t *iperm, unsigned* rng_state),
  (nvtxs, xadj, adjncy, vwgt, options, perm, iperm, rng_state),
  METIS_NODEND_TS,
  metis_nodend_ts,
  metis_nodend_ts_,
  metis_nodend_ts__
)


FRENAME(
  METIS_Free,
  (void *ptr),
  (ptr),
  METIS_FREE,
  metis_free,
  metis_free_,
  metis_free__
)


FRENAME(
  METIS_SetDefaultOptions,
  (idx_t *options),
  (options),
  METIS_SETDEFAULTOPTIONS,
  metis_setdefaultoptions,
  metis_setdefaultoptions_,
  metis_setdefaultoptions__
)
    


