/* This example is taken from the TRACER benchmarks
 * https://doi.org/10.1145/3276505
 */

// Adapted for the tool PSChecker

#include <pthread.h>

#define N 25

int x;

void *thread1(void *arg) {
	int i;
	for (i=0; i<N; i++)
		x = 1;
	return NULL;
}



void *thread2(void *arg) {
	int i;
	for (i=0; i<N; i++)
		x = 2;
	return NULL;
}

void *thread3(void *arg) {

	assert(x != 3);
	return NULL;
}

int main(int argc, char **argv)
{
	pthread_t t1, t2, t3;

	x = 0;

	pthread_create(&t1, NULL, thread1, NULL);
	pthread_create(&t2, NULL, thread2, NULL);
	pthread_create(&t3, NULL, thread3, NULL);

	return 0;
}
