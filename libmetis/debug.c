/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * debug.c
 *
 * This file contains code that performs self debugging
 *
 * Started 7/24/97
 * George
 *
 */

#include "metislib.h"



/*************************************************************************/
/*! This function computes the total edgecut 
 */
/*************************************************************************/
idx_t ComputeCut(graph_t *graph, idx_t *where)
{
  idx_t i, j, cut;

  if (graph->adjwgt == NULL) {
    for (cut=0, i=0; i<graph->nvtxs; i++) {
      for (j=graph->xadj[i]; j<graph->xadj[i+1]; j++)
        if (where[i] != where[graph->adjncy[j]])
          cut++;
    }
  }
  else {
    for (cut=0, i=0; i<graph->nvtxs; i++) {
      for (j=graph->xadj[i]; j<graph->xadj[i+1]; j++)
        if (where[i] != where[graph->adjncy[j]])
          cut += graph->adjwgt[j];
    }
  }

  return cut/2;
}

/*************************************************************************/
/*! This function checks whether or not the boundary information is correct 
 */
/*************************************************************************/
idx_t CheckBnd(graph_t *graph) 
{
  idx_t i, j, nvtxs, nbnd;
  idx_t *xadj, *adjncy, *where, *bndptr, *bndind;

  nvtxs = graph->nvtxs;
  xadj = graph->xadj;
  adjncy = graph->adjncy;
  where = graph->where;
  bndptr = graph->bndptr;
  bndind = graph->bndind;

  for (nbnd=0, i=0; i<nvtxs; i++) {
    if (xadj[i+1]-xadj[i] == 0)
      nbnd++;   /* Islands are considered to be boundary vertices */

    for (j=xadj[i]; j<xadj[i+1]; j++) {
      if (where[i] != where[adjncy[j]]) {
        nbnd++;
        ASSERT(bndptr[i] != -1);
        ASSERT(bndind[bndptr[i]] == i);
        break;
      }
    }
  }

  ASSERTP(nbnd == graph->nbnd, ("%"PRIDX" %"PRIDX"\n", nbnd, graph->nbnd));

  return 1;
}


/*************************************************************************/
/*! This function checks whether or not the boundary information is correct 
 */
/*************************************************************************/
idx_t CheckNodeBnd(graph_t *graph, idx_t onbnd) 
{
  idx_t i, j, nvtxs, nbnd;
  idx_t *xadj, *adjncy, *where, *bndptr, *bndind;

  nvtxs = graph->nvtxs;
  xadj = graph->xadj;
  adjncy = graph->adjncy;
  where = graph->where;
  bndptr = graph->bndptr;
  bndind = graph->bndind;

  for (nbnd=0, i=0; i<nvtxs; i++) {
    if (where[i] == 2) 
      nbnd++;   
  }

  ASSERTP(nbnd == onbnd, ("%"PRIDX" %"PRIDX"\n", nbnd, onbnd));

  for (i=0; i<nvtxs; i++) {
    if (where[i] != 2) {
      ASSERTP(bndptr[i] == -1, ("%"PRIDX" %"PRIDX"\n", i, bndptr[i]));
    }
    else {
      ASSERTP(bndptr[i] != -1, ("%"PRIDX" %"PRIDX"\n", i, bndptr[i]));
    }
  }

  return 1;
}

/*************************************************************************/
/*! This function checks the correctness of the NodeFM data structures 
 */
/*************************************************************************/
idx_t CheckNodePartitionParams(graph_t *graph)
{
  idx_t i, j, k, l, nvtxs, me, other;
  idx_t *xadj, *adjncy, *adjwgt, *vwgt, *where;
  idx_t edegrees[2], pwgts[3];

  nvtxs  = graph->nvtxs;
  xadj   = graph->xadj;
  vwgt   = graph->vwgt;
  adjncy = graph->adjncy;
  adjwgt = graph->adjwgt;
  where  = graph->where;

  /*------------------------------------------------------------
  / Compute now the separator external degrees
  /------------------------------------------------------------*/
  pwgts[0] = pwgts[1] = pwgts[2] = 0;
  for (i=0; i<nvtxs; i++) {
    me = where[i];
    pwgts[me] += vwgt[i];

    if (me == 2) { /* If it is on the separator do some computations */
      edegrees[0] = edegrees[1] = 0;

      for (j=xadj[i]; j<xadj[i+1]; j++) {
        other = where[adjncy[j]];
        if (other != 2)
          edegrees[other] += vwgt[adjncy[j]];
      }
      if (edegrees[0] != graph->nrinfo[i].edegrees[0] || 
          edegrees[1] != graph->nrinfo[i].edegrees[1]) {
        printf("Something wrong with edegrees: %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX"\n", 
            i, edegrees[0], edegrees[1], 
            graph->nrinfo[i].edegrees[0], graph->nrinfo[i].edegrees[1]);
        return 0;
      }
    }
  }

  if (pwgts[0] != graph->pwgts[0] || 
      pwgts[1] != graph->pwgts[1] || 
      pwgts[2] != graph->pwgts[2]) {
    printf("Something wrong with part-weights: %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX"\n", pwgts[0], pwgts[1], pwgts[2], graph->pwgts[0], graph->pwgts[1], graph->pwgts[2]);
    return 0;
  }

  return 1;
}


/*************************************************************************/
/*! This function checks if the separator is indeed a separator 
 */
/*************************************************************************/
idx_t IsSeparable(graph_t *graph)
{
  idx_t i, j, nvtxs, other;
  idx_t *xadj, *adjncy, *where;

  nvtxs = graph->nvtxs;
  xadj = graph->xadj;
  adjncy = graph->adjncy;
  where = graph->where;

  for (i=0; i<nvtxs; i++) {
    if (where[i] == 2)
      continue;
    other = (where[i]+1)%2;
    for (j=xadj[i]; j<xadj[i+1]; j++) {
      ASSERTP(where[adjncy[j]] != other, 
          ("%"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX" %"PRIDX"\n", 
           i, where[i], adjncy[j], where[adjncy[j]], xadj[i+1]-xadj[i], 
           xadj[adjncy[j]+1]-xadj[adjncy[j]]));
    }
  }

  return 1;
}

