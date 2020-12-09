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
         occurs '[173, 180, 221]'  
      id1  'z1'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[165, 182, 222]'  
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
         occurs '[172, 190, 193, 194, 197, 205, 209, 223]'  
      id4  'fib2'  
         type 'int'  kind 'g'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[191, 195, 206, 208, 210, 212, 224]'  
   t0
      id5  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id6  '__lv'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[163, 165, 166]'  
      id7  '_n'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[164, 172, 173]'  
   t1
      id8  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id9  '__lv'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[179, 180, 181]'  
   t2
      id10  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id11  '_x'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[187, 190, 192, 194, 196]'  
      id12  '_y'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[188, 191, 192, 195, 196]'  
      id13  '_s'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[192, 193, 196, 197]'  
   t3
      id14  '__cs_unused'  
         type 'void *'  kind 'p'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[]'  
      id15  '_x'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[202, 205, 207, 209, 211]'  
      id16  '_y'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[203, 206, 207, 210, 211]'  
      id17  '_s'  
         type 'static int'  kind 'l'  arity '0'  
         size '[]'  
         ref '[]'  
         deref '[]'  
         occurs '[207, 208, 211, 212]'  
   main
      id18  'thr0'  
         type 'static __cs_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[227]'  
         deref '[]'  
         occurs '[227]'  
      id19  'thr1'  
         type 'static __cs_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[228]'  
         deref '[]'  
         occurs '[228]'  
      id20  'thr2'  
         type 'static __cs_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[225]'  
         deref '[]'  
         occurs '[225]'  
      id21  'thr3'  
         type 'static __cs_t'  kind 'l'  arity '0'  
         size '[]'  
         ref '[226]'  
         deref '[]'  
         occurs '[226]'  

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
    static int __lv;
    __lv = 0;
    static int _n;
    _n = __CSEQ_nondet_int();
    rlx_read_ps(z1, __lv);
    if (__lv == 1)
    {
        __CSEQ_assert(0);
    }
    else
    {
        rlx_read_ps(fib1, _n);
        rlx_write_ps(var0, _n);
    }

    __exit_t0:
    ;

    __cs_exit(0);
}


void *__cs_unused
void *
function 't1' ----------------------------------:
void *t1(void *__cs_unused)
{
    static int __lv;
    __lv = __CSEQ_nondet_int();
    rlx_read_ps(var0, __lv);
    __CSEQ_assume(__lv == 8);
    rlx_write_ps(z1, 1);
    __exit_t1:
    ;

    __cs_exit(0);
}


void *__cs_unused
void *
function 't2' ----------------------------------:
void *t2(void *__cs_unused)
{
    static int _x;
    _x = __CSEQ_nondet_int();
    static int _y;
    _y = __CSEQ_nondet_int();
    static int _s;
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);
    __exit_t2:
    ;

    __cs_exit(0);
}


void *__cs_unused
void *
function 't3' ----------------------------------:
void *t3(void *__cs_unused)
{
    static int _x;
    _x = __CSEQ_nondet_int();
    static int _y;
    _y = __CSEQ_nondet_int();
    static int _s;
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);
    __exit_t3:
    ;

    __cs_exit(0);
}


void *__cs_unused
void *
function 'main' ----------------------------------:
int main()
{
    static __cs_t thr0;
    ;
    static __cs_t thr1;
    ;
    static __cs_t thr2;
    ;
    static __cs_t thr3;
    ;
    var0 = 0;
    z1 = 0;
    fib1 = 1;
    fib2 = 1;
    __cs_create(&thr2, 0, t2, 0);
    __cs_create(&thr3, 0, t3, 0);
    __cs_create(&thr0, 0, t0, 0);
    __cs_create(&thr1, 0, t1, 0);
    goto __exit_main;
    __exit_main:
    ;

    __cs_exit(0);
}



int
Last statement, by function:
function: t0   stmt:     __cs_exit(0);

function: t1   stmt:     __cs_exit(0);

function: t2   stmt:     __cs_exit(0);

function: t3   stmt:     __cs_exit(0);

function: main   stmt:     __cs_exit(0);


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
