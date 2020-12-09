list of functions:
   t0(param: __cs_unused)  call count 0
   t1(param: __cs_unused)  call count 0
   t2(param: __cs_unused)  call count 0
   t3(param: __cs_unused)  call count 0
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
         occurs '[173, 179, 217]'  
      id1  'z1'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[165, 181, 218]'  
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
         occurs '[172, 188, 191, 192, 195, 202, 206, 219]'  
      id4  'fib2'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[189, 193, 203, 205, 207, 209, 220]'  
   t0
      id5  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id6  '__lv'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[163, 165, 166]'  
      id7  '_n'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[172, 173]'  
   t1
      id8  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id9  '__lv'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[179, 180]'  
   t2
      id10  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id11  '_x'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[188, 190, 192, 194]'  
      id12  '_y'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[189, 190, 193, 194]'  
      id13  '_s'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[190, 191, 194, 195]'  
   t3
      id14  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id15  '_x'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[202, 204, 206, 208]'  
      id16  '_y'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[203, 204, 207, 208]'  
      id17  '_s'  
         type 'int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[204, 205, 208, 209]'  
   main
      id18  'thr0'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[223]'  
         deref '[]'  
         occurs '[223]'  
      id19  'thr1'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[224]'  
         deref '[]'  
         occurs '[224]'  
      id20  'thr2'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[221]'  
         deref '[]'  
         occurs '[221]'  
      id21  'thr3'  
         type 'pthread_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[222]'  
         deref '[]'  
         occurs '[222]'  

Fields:

Typedefs:

Pointer variables:
   (global)
   t0
       var '__cs_unused'   type 'void *'   kind 'p'   arity '0'   size '[]'   
   t1
       var '__cs_unused'   type 'void *'   kind 'p'   arity '0'   size '[]'   
   t2
       var '__cs_unused'   type 'void *'   kind 'p'   arity '0'   size '[]'   
   t3
       var '__cs_unused'   type 'void *'   kind 'p'   arity '0'   size '[]'   
   main

Function blocks:
function 't0' ----------------------------------:
void *t0(void *__cs_unused)
{
    int __lv;
    __lv = 0;
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


void *__cs_unused
void *
function 't1' ----------------------------------:
void *t1(void *__cs_unused)
{
    int __lv;
    rlx_read_ps(var0, __lv);
    assume(__lv == 8);
    rlx_write_ps(z1, 1);
}


void *__cs_unused
void *
function 't2' ----------------------------------:
void *t2(void *__cs_unused)
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


void *__cs_unused
void *
function 't3' ----------------------------------:
void *t3(void *__cs_unused)
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


void *__cs_unused
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
   (6, '__cs_unused')  
   (7, '__lv')  
   (8, '_n')  
   (9, 't1')  
   (10, '__cs_unused')  
   (11, '__lv')  
   (12, 't2')  
   (13, '__cs_unused')  
   (14, '_x')  
   (15, '_y')  
   (16, '_s')  
   (17, 't3')  
   (18, '__cs_unused')  
   (19, '_x')  
   (20, '_y')  
   (21, '_s')  
   (22, 'main')  
   (23, 'thr0')  
   (24, 'thr1')  
   (25, 'thr2')  
   (26, 'thr3')  
