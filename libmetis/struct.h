/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * struct.h
 *
 * This file contains data structures for ILU routines.
 *
 * Started 9/26/95
 * George
 *
 * $Id: struct.h 14362 2013-05-21 21:35:23Z karypis $
 */

#ifndef _LIBMETIS_STRUCT_H_
#define _LIBMETIS_STRUCT_H_

/*************************************************************************/
/*! The following data structure holds information on degrees for k-way
    partition */
/*************************************************************************/
typedef struct nrinfo_t {
 idx_t edegrees[2];  
} nrinfo_t;


/*************************************************************************/
/*! This data structure holds a graph */
/*************************************************************************/
typedef struct graph_t {
  idx_t nvtxs, nedges;	/* The # of vertices and edges in the graph */
  idx_t ncon;		/* The # of constrains */ 
  idx_t *xadj;		/* Pointers to the locally stored vertices */
  idx_t *vwgt;		/* Vertex weights */
  idx_t *vsize;		/* Vertex sizes for min-volume formulation */
  idx_t *adjncy;        /* Array that stores the adjacency lists of nvtxs */
  idx_t *adjwgt;        /* Array that stores the weights of the adjacency lists */

  idx_t *tvwgt;         /* The sum of the vertex weights in the graph */
  real_t *invtvwgt;     /* The inverse of the sum of the vertex weights in the graph */


  /* These are to keep track control if the corresponding fields correspond to
     application or library memory */
  int free_xadj, free_vwgt, free_vsize, free_adjncy, free_adjwgt;

  idx_t *cmap;  /* The contraction/coarsening map */

  idx_t *label; /* The labels of the vertices for recursive bisection (pmetis/ometis) */

  /* Partition parameters */
  idx_t mincut, minvol;
  idx_t *where, *pwgts;
  idx_t nbnd;
  idx_t *bndptr, *bndind;

  /* Bisection refinement parameters */
  idx_t *id, *ed;

  /* Node refinement information */
  nrinfo_t *nrinfo;

  /* keep track of the dropped edgewgt */
  idx_t droppedewgt;

  /* the linked-list structure of the sequence of graphs */
  struct graph_t *coarser, *finer;

} graph_t;

/*************************************************************************/
/*! The following structure stores information used by Metis */
/*************************************************************************/
typedef struct ctrl_t {
  moptype_et  optype;	        /* Type of operation */
  mobjtype_et objtype;          /* Type of refinement objective */
  mdbglvl_et  dbglvl;		/* Controls the debugging output of the program */
  mctype_et   ctype;		/* The type of coarsening */
  miptype_et  iptype;		/* The type of initial partitioning */
  mrtype_et   rtype;		/* The type of refinement */

  idx_t CoarsenTo;		/* The # of vertices in the coarsest graph */
  idx_t nIparts;                /* The number of initial partitions to compute */
  idx_t no2hop;                 /* Indicates if 2-hop matching will be used */
  idx_t minconn;                /* Indicates if the subdomain connectivity will be minimized */
  idx_t contig;                 /* Indicates if contiguous partitions are required */
  idx_t nseps;			/* The number of separators to be found during multiple bisections */
  idx_t ufactor;                /* The user-supplied load imbalance factor */
  idx_t compress;               /* If the graph will be compressed prior to ordering */
  idx_t ccorder;                /* If connected components will be ordered separately */
  idx_t seed;                   /* The seed for the random number generator */
  idx_t ncuts;                  /* The number of different partitionings to compute */
  idx_t niter;                  /* The number of iterations during each refinement */
  idx_t dropedges;              /* Indicates if edges will be randomly dropped during coarsening */
  idx_t *maxvwgt;		/* The maximum allowed weight for a vertex */

  idx_t ncon;                   /*!< The number of balancing constraints */
  idx_t nparts;                 /*!< The number of partitions */

  real_t pfactor;		/* .1*(user-supplied prunning factor) */

  real_t *ubfactors;            /*!< The per-constraint ubfactors */
  
  real_t *tpwgts;               /*!< The target partition weights */
  real_t *pijbm;                /*!< The nparts*ncon multiplies for the ith partition
                                     and jth constraint for obtaining the balance */

  real_t cfactor;               /*!< The achieved compression factor */

  /* Workspace information */
  gk_mcore_t *mcore;    /*!< The persistent memory core for within function 
                             mallocs/frees */

  /* The subdomain graph, in sparse format  */ 
  idx_t *maxnads;               /* The maximum allocated number of adjacent domains */
  idx_t *nads;                  /* The number of adjacent domains */
  idx_t **adids;                /* The IDs of the adjacent domains */
  idx_t **adwgts;               /* The edge-weight to the adjacent domains */
  idx_t *pvec1, *pvec2;         /* Auxiliary nparts-size vectors for efficiency */

  unsigned rng_state;
  
} ctrl_t;



#endif
