/*!
\file  
\brief Various routines for providing portable 32 and 64 bit random number
       generators.

\date   Started 5/17/2007
\author George
\version\verbatim $Id: random.c 11793 2012-04-04 21:03:02Z karypis $ \endverbatim
*/

#include <GKlib.h>

/*************************************************************************/
/*! Define function rand_r, which may not exist on certain machines */
/*************************************************************************/
int my_rand_r(unsigned *state) {
  // Linear congruential generator, with values from wikipedia
  int result = ((*state * 1103515245) + 12345) & 0x7fffffff;
  *state = result;
  return result;
}

/* generates a random number on [0, 2^64-1]-interval */
uint64_t gk_randint64(unsigned* state)
{
uint64_t piece_1 = ((uint64_t) my_rand_r(state)) << 32;
uint64_t piece_2 = ((uint64_t) my_rand_r(state));
  return (uint64_t)(piece_1 | piece_2);
}

/* generates a random number on [0, 2^32-1]-interval */
uint32_t gk_randint32(unsigned* state)
{
  return (uint32_t)my_rand_r(state);
}


