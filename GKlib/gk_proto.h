/*!
\file gk_proto.h
\brief This file contains function prototypes

\date   Started 3/27/2007
\author George
\version\verbatim $Id: gk_proto.h 12591 2012-09-01 19:03:15Z karypis $ \endverbatim
*/

#ifndef _GK_PROTO_H_
#define _GK_PROTO_H_

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------------------------------------------
 * memory.c
 *-------------------------------------------------------------*/
GK_MKALLOC_PROTO(gk_idx, gk_idx_t)

int    gk_malloc_init();
void   gk_malloc_cleanup(int showstats);
void  *gk_malloc(size_t nbytes, char *msg);
void  *gk_realloc(void *oldptr, size_t nbytes, char *msg);
void   gk_free(void **ptr1,...);

/*-------------------------------------------------------------
 * error.c
 *-------------------------------------------------------------*/
void gk_errexit(int signum, char *,...);

/*-------------------------------------------------------------
 * random.c
 *-------------------------------------------------------------*/
uint64_t gk_randint64(unsigned* state);
uint32_t gk_randint32(unsigned* state);
int my_rand_r(unsigned *state);

/* mcore.c */
gk_mcore_t *gk_mcoreCreate(size_t coresize);
gk_mcore_t *gk_gkmcoreCreate();
void gk_mcoreDestroy(gk_mcore_t **r_mcore, int showstats);
void gk_gkmcoreDestroy(gk_mcore_t **r_mcore, int showstats);
void *gk_mcoreMalloc(gk_mcore_t *mcore, size_t nbytes);
void gk_mcorePush(gk_mcore_t *mcore);
void gk_gkmcorePush(gk_mcore_t *mcore);
void gk_mcorePop(gk_mcore_t *mcore);
void gk_gkmcorePop(gk_mcore_t *mcore);
void gk_mcoreAdd(gk_mcore_t *mcore, int type, size_t nbytes, void *ptr);
void gk_gkmcoreAdd(gk_mcore_t *mcore, int type, size_t nbytes, void *ptr);
void gk_mcoreDel(gk_mcore_t *mcore, void *ptr);
void gk_gkmcoreDel(gk_mcore_t *mcore, void *ptr);


#ifdef __cplusplus
}
#endif


#endif

