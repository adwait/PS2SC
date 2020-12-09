list of functions:
   t0(param: )  call count 0
   t1(param: )  call count 0
   t2(param: )  call count 0
   t3(param: )  call count 0
   main(param: )  call count 0

list of thread functions:
   t2  call count 1
   t3  call count 1
   t0  call count 1
   t1  call count 1

parameters for main():
   (no params)

Variables:
   (global)
      id0  'var0'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[204, 212, 266]'  
      id1  'z1'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[194, 215, 269]'  
      id2  'casvar'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id3  'fib1'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[203, 225, 228, 230, 233, 249, 254, 271]'  
      id4  'fib2'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[226, 231, 250, 252, 255, 257, 272]'  
   t0
      id5  '__lv'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[194, 195]'  
      id6  '_n'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[203, 204]'  
   t1
      id7  '__lv'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[212, 213]'  
   t2
      id8  '_x'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[225, 227, 230, 232]'  
      id9  '_y'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[226, 227, 231, 232]'  
      id10  '_s'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[227, 228, 232, 233]'  
   t3
      id11  '_x'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[249, 251, 254, 256]'  
      id12  '_y'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[250, 251, 255, 256]'  
      id13  '_s'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[251, 252, 256, 257]'  
   main
      id14  'thr0'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[276]'  
         deref '[]'  
         occurs '[276]'  
      id15  'thr1'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[277]'  
         deref '[]'  
         occurs '[277]'  
      id16  'thr2'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[274]'  
         deref '[]'  
         occurs '[274]'  
      id17  'thr3'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[275]'  
         deref '[]'  
         occurs '[275]'  

Fields:

Typedefs:

Pointer variables:
   (global)
   t0
   t1
   t2
   t3
   main

Function blocks:
function 't0' ----------------------------------:
void *t0()
{
    int __lv = 0;
    int _n;
    rlx_read_ps(z1, __lv);
    if (__lv == 1)
    {
        assert(0);
    }
    else
    {
        rlx_read_ps(fib1, _n);
        rlx_write_ps(var0, _n);
    }

}



void *
function 't1' ----------------------------------:
void *t1()
{
    int __lv;
    rlx_read_ps(var0, __lv);
    assume(__lv == 8);
    rlx_write_ps(z1, 1);
}



void *
function 't2' ----------------------------------:
void *t2()
{
    int _x;
    int _y;
    int _s;
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);
}



void *
function 't3' ----------------------------------:
void *t3()
{
    int _x;
    int _y;
    int _s;
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);
}



void *
function 'main' ----------------------------------:
int main()
{
    pthread_t thr0;
    pthread_t thr1;
    pthread_t thr2;
    pthread_t thr3;
    var0 = 0;
    z1 = 0;
    fib1 = 1;
    fib2 = 1;
    pthread_create(&thr2, 0, t2, 0);
    pthread_create(&thr3, 0, t3, 0);
    pthread_create(&thr0, 0, t0, 0);
    pthread_create(&thr1, 0, t1, 0);
    return 0;
}



int
Last statement, by function:
function: t0   stmt:     if (__lv == 1)
    {
        assert(0);
    }
    else
    {
        rlx_read_ps(fib1, _n);
        rlx_write_ps(var0, _n);
    }


function: t1   stmt:     rlx_write_ps(z1, 1);

function: t2   stmt:     rlx_write_ps(fib1, _s);

function: t3   stmt:     rlx_write_ps(fib2, _s);

function: main   stmt:     return 0;


All symbols (new symbol table - work in progress):
   (0, 'var0')  
   (1, 'z1')  
   (2, 'casvar')  
   (3, 'fib1')  
   (4, 'fib2')  
   (5, 't0')  
   (6, '__lv')  
   (7, '_n')  
   (8, 't1')  
   (9, '__lv')  
   (10, 't2')  
   (11, '_x')  
   (12, '_y')  
   (13, '_s')  
   (14, 't3')  
   (15, '_x')  
   (16, '_y')  
   (17, '_s')  
   (18, 'main')  
   (19, 'thr0')  
   (20, 'thr1')  
   (21, 'thr2')  
   (22, 'thr3')  
