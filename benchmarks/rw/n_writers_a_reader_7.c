/* CDSChecker example 
 * https://dl.acm.org/citation.cfm?id=2914585.2806886, page 10, section 5.4
 */

// Adapted for the tool PSChecker

#include <pthread.h>

#define N 7

int  x;


void *writer1(void *arg) {
  rlx_write_ps(x, 1);
  return NULL;
}

void *writer2(void *arg) {
  rlx_write_ps(x, 2);
  return NULL;
}

void *writer3(void *arg) {
  rlx_write_ps(x, 3);
  return NULL;
}

void *writer4(void *arg) {
  rlx_write_ps(x, 4);
  return NULL;
}

void *writer5(void *arg) {
  rlx_write_ps(x, 5);
  return NULL;
}

void *writer6(void *arg) {
  rlx_write_ps(x, 6);
  return NULL;
}

void *writer7(void *arg) {
  rlx_write_ps(x, 7);
  return NULL;
}

void *reader(void *arg) {
  int r1;
  rlx_read_ps(x, r1);
  if (r1 == 11){
    assert(0);
  }
  return NULL;
}



int main()
{
  pthread_t t1;
  pthread_t t2;
  pthread_t t3;
  pthread_t t4;
  pthread_t t5;
  pthread_t t6;
  pthread_t t7;
  pthread_t r;

  x = 0;
  
  pthread_create(&t1, NULL,  writer1, NULL);
  pthread_create(&t2, NULL,  writer2, NULL);
  pthread_create(&t3, NULL,  writer3, NULL);
  pthread_create(&t4, NULL,  writer4, NULL);
  pthread_create(&t5, NULL,  writer5, NULL);
  pthread_create(&t6, NULL,  writer6, NULL);
  pthread_create(&t7, NULL,  writer7, NULL);
  pthread_create(&r, NULL,  reader, NULL);

  return 0;
}
