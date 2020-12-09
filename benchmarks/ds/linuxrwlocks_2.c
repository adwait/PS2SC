/* This example is taken from the TRACER benchmarks
 */

/* The original benchmark is from CDSChecker */

/* Adapted for the tool PSChecker */

#include <pthread.h>

#define LOOP 3
#define OUTER_LOOP 2

#define RW_LOCK_BIAS            0x00100000

int __cs_mlock;
int lock;


void *treader(void *unused){
	int priorvalue;
	int i, j, OK;
	int _lock;

	__cs_mutex_lock(&__cs_mlock);;
	sc_fence();

	rlx_read_ps(lock, priorvalue);
	rlx_write_ps(lock, priorvalue - 1);
	
	sc_fence();
	__cs_mutex_unlock(&__cs_mlock);

	OK = 0;

	for (i = 0; i < OUTER_LOOP; i++){
		if(priorvalue <= 0){
			__cs_mutex_lock(&__cs_mlock);
			sc_fence();
			
			rlx_read_ps(lock, _lock);
			rlx_write_ps(lock, _lock + 1);
			
			sc_fence();
			__cs_mutex_unlock(&__cs_mlock);
			
			OK = 0;

			for (j = 0; j < LOOP; j++){
				rlx_read_ps(lock,_lock);
				if (_lock <= 0)
				{
					__CPROVER_assert(0);
				}
				else{
					OK = 1;
					break;
				}
			}

			if (OK == 1)
			{
				__cs_mutex_lock(&__cs_mlock);;
				sc_fence();
				
				rlx_read_ps(lock, priorvalue);
				rlx_write_ps(lock, priorvalue - 1);
				
				sc_fence();
				__cs_mutex_unlock(&__cs_mlock);
			}
		}
		else{
			break;
		}
	}
	
	lock = lock + 1;
	
	return NULL;
}

void *twriter(void *unused)
{
	int priorvalue;
	int i, j, OK;
	int _lock;

	__cs_mutex_lock(&__cs_mlock);;
	sc_fence();
	
	rlx_read_ps(lock, priorvalue);
	rlx_write_ps(lock, priorvalue - RW_LOCK_BIAS);
	
	sc_fence();
	__cs_mutex_unlock(&__cs_mlock);

	OK = 0;

	for (i = 0; i < OUTER_LOOP; i++){
		if(priorvalue != RW_LOCK_BIAS){
			
			__cs_mutex_lock(&__cs_mlock);;
			sc_fence();
			
			rlx_read_ps(lock, _lock);
			rlx_write_ps(lock, _lock + RW_LOCK_BIAS);
			
			sc_fence();
			__cs_mutex_unlock(&__cs_mlock);
			
			OK = 0;

			for (j = 0; j < LOOP; j++){
				rlx_read_ps(lock, _lock);
				if (_lock != RW_LOCK_BIAS)
				{
					__CPROVER_assert(0);
				}
				else{
					OK = 1;
					break;
				}
			}

			if (OK == 1)
			{
				__cs_mutex_lock(&__cs_mlock);;
				sc_fence();
				
				rlx_read_ps(lock, priorvalue);
				rlx_write_ps(lock, priorvalue - RW_LOCK_BIAS);
					
				sc_fence();
				__cs_mutex_unlock(&__cs_mlock);
			}
		}
		else{
			break;
		}
	}

	// __cs_mutex_lock(&__cs_mlock);;
	// sc_fence();
	
	// lock = lock + RW_LOCK_BIAS;
	
	// sc_fence();
	// __cs_mutex_unlock(&__cs_mlock);


	return NULL;
}


int main()
{
	pthread_t t1, t2;
	
	__cs_mutex_init(&__cs_mlock, 0);
	lock = RW_LOCK_BIAS;

	pthread_create(&t1, NULL, treader, 0);
	pthread_create(&t2, NULL, twriter, 0);

	return 0;
}
