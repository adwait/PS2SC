/* Implemented under the RA semantics
 * This benchmark is part of TRACER
 * Need to use fences under RA to avoid 
 * a violation of mutual execlusion property
 * Get orgiral source code from: 
 * https://github.com/pramalhe/ConcurrencyFreaks/blob/master/C11/papers/cralgorithm/HehnerC11.c
 */

// Eric C. R. Hehner and R. K. Shyamasundar, An Implementation of P and V, Information Processing Letters, 1981, 12(4),
// pp. 196-197

// #include <stdlib.h>
#include <pthread.h>
// #include <assert.h>
// #include "stdatomic.h"

#define LOOP 3
#define N 3

// enum { MAX_TICKET = INTPTR_MAX };
#define MAX_TICKET 0xffffffff
// shared variables
int ticket[N];
int var;

// atomic_int __fence_var;

void *Worker0(void *arg)
{
  	int id = 0;
    int ok;
    int max, j, jj, v;
    int __ticket;
  
    ticket[id] = 0;
  
    sc_fence();

    max = 0;
    
    for (j=0; j<N; j+=1) {
      v = ticket[j];
      if (max < v && v != MAX_TICKET ) max = v;
    } // for
    max = max + 1;
  
    ticket[id] = max;

    // atomic_fetch_add_explicit(&__fence_var, 0, memory_order_acq_rel);
    sc_fence();

    for (j = 0; j<N; j+=1 ) {
      ok = 0;
      for (jj=0; jj<LOOP; jj++) {
        __ticket = ticket[j];
        if (!( __ticket < max || __ticket == max && j < id ) ) {
          ok = 1;
          break;
        }  
      }
      if (ok==0) return NULL;
    }

    sc_fence();


  
    // critical section
    var = id+1;
    assert(var == id);

    ticket[id] = MAX_TICKET;
	
    return NULL;

} // Worker

void *Worker1(void *arg)
{
    int id = 1;
    int ok;
    int max, j, jj, v;
    int __ticket;
  
    ticket[id] = 0;
  
    sc_fence();

    max = 0;
    
    for (j=0; j<N; j+=1) {
      v = ticket[j];
      if (max < v && v != MAX_TICKET ) max = v;
    } // for
    max = max + 1;
  
    ticket[id] = max;

    // atomic_fetch_add_explicit(&__fence_var, 0, memory_order_acq_rel);
    sc_fence();

    for (j = 0; j<N; j+=1 ) {
      ok = 0;
      for (jj=0; jj<LOOP; jj++) {
        __ticket = ticket[j];
        if (!( __ticket < max || __ticket == max && j < id ) ) {
          ok = 1;
          break;
        }  
      }
      if (ok==0) return NULL;
    }

    sc_fence();

    // critical section
    var = id;
    assert(var == id);

    ticket[id] = MAX_TICKET;
  
    return NULL;

} // Worker

void *Worker2(void *arg)
{
    int id = 2;
    int ok;
    int max, j, jj, v;
    int __ticket;
  
    ticket[id] = 0;
  
    sc_fence();

    max = 0;
    
    for (j=0; j<N; j+=1) {
      v = ticket[j];
      if (max < v && v != MAX_TICKET ) max = v;
    } // for
    max = max + 1;
  
    ticket[id] = max;

    // atomic_fetch_add_explicit(&__fence_var, 0, memory_order_acq_rel);
    sc_fence();

    for (j = 0; j<N; j+=1 ) {
      ok = 0;
      for (jj=0; jj<LOOP; jj++) {
        __ticket = ticket[j];
        if (!( __ticket < max || __ticket == max && j < id ) ) {
          ok = 1;
          break;
        }  
      }
      if (ok==0) return NULL;
    }

    sc_fence();


  
    // critical section
    var = id;
    assert(var == id);

    ticket[id] = MAX_TICKET;
  
    return NULL;

} // Worker


int main(int argc, char **argv)
{
  	pthread_t ts0, ts1, ts2;
  	
  	// for (i=0; i<N; i++) {
  	ticket[0] = MAX_TICKET;
    ticket[1] = MAX_TICKET;
    ticket[2] = MAX_TICKET;
  	// }
  	var = 0;
  	// atomic_init(&__fence_var, 0);
  	  
  	// for (int i=0; i<N; i++) {
    // arg[i] = i;
  	pthread_create(&ts0, NULL, Worker0, NULL);
    pthread_create(&ts1, NULL, Worker1, NULL);
    pthread_create(&ts2, NULL, Worker2, NULL);
  	// }
  
  	return 0;
}

