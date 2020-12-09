/* Adapted from https://github.com/sosy-lab/sv-benchmarks/blob/master/c/pthread/queue_ok.c
 *
 */

// Adapted for the tool PSChecker

#include <pthread.h>

#define SIZE (3)
#define EMPTY (-1)
#define TRUE (1)
#define FALSE (0)

// params : --ee 100

int element[SIZE]; 
int head;
int tail;
int amount;

int __cs_mlock;

int stored_elements[SIZE];
int enqueue_flag;
int dequeue_flag;


int empty(void) 
{
  int _head, _tail, _amount;
  _head = head;
  _tail = tail;
  _amount = amount;
  
  if (_head == _tail && _amount==0) 
  { 
    return EMPTY;
  }
  else 
    return 0;
}

int enqueue(int x){
    int _tail, _amount;
    
    _tail = tail;
    element[_tail] = x;

    _amount = amount;
    amount = _amount + 1;

    if (_tail == SIZE-1){
        tail = 0;
    } 
    else{
        tail = _tail + 1;
    }

    return 0;
}

int dequeue() {
	int x, _head, _amount;

	_head = head;
	x = element[_head];

	_amount = amount;
	amount = _amount - 1;

	if (_head == SIZE-1) 
	{
	    head = 0;
	} 
	else {
		head = _head + 1;
	}
	return x;
}


void *te0(){
    int value, i;//, _enqueue_flag;
    int enqueue_number = 0;

    value = 0;

    __cs_mutex_lock(&__cs_mlock);

    if(enqueue_flag != 0){
        
        sc_fence();
        
        for(i=0; i<SIZE; i++){
            if (amount != SIZE){
                value = enqueue_number + value;
                enqueue_number++;
                enqueue(value);
                stored_elements[i] = value;
                
                if(empty()){
                    __CPROVER_assert(0);
                }

            }
        }
        
        sc_fence();

        enqueue_flag = FALSE;
        dequeue_flag = TRUE;
    } 
  
    __cs_mutex_unlock(&__cs_mlock);

}

void *td0(){
    int i; //, _dequeue_flag
    int _stored_elements_i;
    int _dequeue_val;

    __cs_mutex_lock(&__cs_mlock);

    if (dequeue_flag != 0){
        
        sc_fence();

        for(i=0; i<SIZE; i++){
            if(empty() != EMPTY){
                _stored_elements_i = stored_elements[i];
                _dequeue_val = dequeue();
                if (!(_dequeue_val == _stored_elements_i)) {
                    __CPROVER_assert(0);
                }
            }
        }

        dequeue_flag = FALSE;
        enqueue_flag = TRUE; 

        sc_fence();         
    }

    __cs_mutex_unlock(&__cs_mlock);    
}

int main(){
	pthread_t thr0; 
	pthread_t thr1;
	pthread_t thr2;

	int i;
	head = 0;
	tail = 0;
	amount = 0;
	__cs_mutex_init(&__cs_mlock, 0);
	
    for (i = 0; i < SIZE; i++)
	{
		element[i] = 0;
	}

	enqueue_flag = TRUE;
	dequeue_flag = FALSE;

	for (i = 0; i < SIZE; i++)
	{
		stored_elements[i] = 0;
	}


	pthread_create(&thr0, 0, te0, 0);
	pthread_create(&thr1, 0, td0, 0);
	pthread_create(&thr2, 0, te0, 0);

	return 0;
}
