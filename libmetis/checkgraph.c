/*
 * Copyright 1997, Regents of the University of Minnesota
 *
 * checkgraph.c
 *
 * This file contains routines related to I/O
 *
 * Started 8/28/94
 * George
 *
 */

#include "metislib.h"



/*************************************************************************/
/*! This function checks if a graph is valid. A valid graph must satisfy 
    the following constraints:
    - It should contain no self-edges.
    - It should be undirected; i.e., (u,v) and (v,u) should be present.
    - The adjacency list should not contain multiple edges to the same
      other vertex.

    \param graph is the graph to be checked, whose numbering starts from 0.
    \param numflag is 0 if error reporting will be done using 0 as the
           numbering, or 1 if the reporting should be done using 1.
    \param verbose is 1 the identified errors will be displayed, or 0, if
           it should run silently.
*/
/*************************************************************************/
int CheckGraph(graph_t *graph, int numflag, int verbose)
{
  idx_t i, j, k, l;
  idx_t nvtxs, err=0;
  idx_t minedge, maxedge, minewgt, maxewgt;
  idx_t *xadj, *adjncy, *adjwgt, *htable;

  numflag = (numflag == 0 ? 0 : 1);  /* make sure that numflag is 0 or 1 */

  nvtxs  = graph->nvtxs;
  xadj   = graph->xadj;
  adjncy = graph->adjncy;
  adjwgt = graph->adjwgt;

  htable = ismalloc(nvtxs, 0, "htable");

  if (graph->nedges > 0) {
    minedge = maxedge = adjncy[0];
    if (adjwgt) 
      minewgt = maxewgt = adjwgt[0];
  }

  for (i=0; i<nvtxs; i++) {
    for (j=xadj[i]; j<xadj[i+1]; j++) {
      k = adjncy[j];

      minedge = (k < minedge) ? k : minedge;
      maxedge = (k > maxedge) ? k : maxedge;
      if (adjwgt) {
        minewgt = (adjwgt[j] < minewgt) ? adjwgt[j] : minewgt;
        maxewgt = (adjwgt[j] > maxewgt) ? adjwgt[j] : maxewgt;
      }

      if (i == k) {
        if (verbose)
          printf("Vertex %"PRIDX" contains a self-loop "
                 "(i.e., diagonal entry in the matrix)!\n", i+numflag);
        err++;
      }
      else {
        for (l=xadj[k]; l<xadj[k+1]; l++) {
          if (adjncy[l] == i) {
            if (adjwgt) {
              if (adjwgt[l] != adjwgt[j]) {
                if (verbose) 
                  printf("Edges (u:%"PRIDX" v:%"PRIDX" wgt:%"PRIDX") and "
                         "(v:%"PRIDX" u:%"PRIDX" wgt:%"PRIDX") "
                         "do not have the same weight!\n", 
                         i+numflag, k+numflag, adjwgt[j],
                         k+numflag, i+numflag, adjwgt[l]);
                err++;
              }
            }
            break;
          }
        }
        if (l == xadj[k+1]) {
          if (verbose)
            printf("Missing edge: (%"PRIDX" %"PRIDX")!\n", k+numflag, i+numflag);
          err++;
        }
      }

      if (htable[k] == 0) {
        htable[k]++;
      }
      else {
        if (verbose)
          printf("Edge %"PRIDX" from vertex %"PRIDX" is repeated %"PRIDX" times\n", 
              k+numflag, i+numflag, htable[k]++);
        err++;
      }
    }

    for (j=xadj[i]; j<xadj[i+1]; j++) 
      htable[adjncy[j]] = 0;
  }

 
  if (err > 0 && verbose) { 
    printf("A total of %"PRIDX" errors exist in the input file. "
           "Correct them, and run again!\n", err);
  }

  gk_free((void **)&htable, LTERM);

  return (err == 0 ? 1 : 0);
}

