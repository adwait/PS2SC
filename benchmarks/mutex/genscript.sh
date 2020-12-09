#!/bin/bash

if [[ $1 = "2a" ]]; then
	./genpeter.py 4 p 1 > Table2/2a/peterson_4_fenced.c;
	./genpeter.py 6 p 1 > Table2/2a/peterson_6_fenced.c;
	./genpeter.py 8 p 1 > Table2/2a/peterson_8_fenced.c;
	./genpeter.py 10 p 1 > Table2/2a/peterson_10_fenced.c;
	echo Table2/2a done;
elif [[ $1 = "2b" ]]; then
	./genpeter.py 4 s 1 > Table2/2b/szymanski_4_fenced.c;
	./genpeter.py 6 s 1 > Table2/2b/szymanski_6_fenced.c;
	./genpeter.py 8 s 1 > Table2/2b/szymanski_8_fenced.c;
	./genpeter.py 10 s 1 > Table2/2b/szymanski_10_fenced.c;
	echo Table2/2b done;
elif [[ $1 = "3" ]]; then
	./genpeter.py 3 p 0 > Table3/peterson_3_fenced.c;
	./genpeter.py 4 p 0 > Table3/peterson_4_fenced.c;
	./genpeter.py 5 p 0 > Table3/peterson_5_fenced.c;
	./genpeter.py 6 p 0 > Table3/peterson_6_fenced.c;
	./genpeter.py 7 p 0 > Table3/peterson_7_fenced.c;
	echo Table3 done;		
elif [[ $1 = "4" ]]; then
	./genpeter.py 3 p 0 > Table4/peterson_3_fenced.c;
	./genpeter.py 4 p 0 > Table4/peterson_4_fenced.c;
	./genpeter.py 5 p 0 > Table4/peterson_5_fenced.c;
	./genpeter.py 6 p 0 > Table4/peterson_6_fenced.c;
	./genpeter.py 7 p 0 > Table4/peterson_7_fenced.c;
	echo Table4 done;		
elif [[ $1 = "5" ]]; then
	./genpeter.py 3 s 0 > Table5/szymanski_3_fenced.c;
	./genpeter.py 4 s 0 > Table5/szymanski_4_fenced.c;
	./genpeter.py 5 s 0 > Table5/szymanski_5_fenced.c;
	./genpeter.py 6 s 0 > Table5/szymanski_6_fenced.c;
	./genpeter.py 7 s 0 > Table5/szymanski_7_fenced.c;
	echo Table5 done;		
elif [[ $1 = "5" ]]; then
	./genpeter.py 3 s 0 > Table5/szymanski_3_fenced.c;
	./genpeter.py 4 s 0 > Table5/szymanski_4_fenced.c;
	./genpeter.py 5 s 0 > Table5/szymanski_5_fenced.c;
	./genpeter.py 6 s 0 > Table5/szymanski_6_fenced.c;
	./genpeter.py 7 s 0 > Table5/szymanski_7_fenced.c;
	echo Table5 done;		
elif [[ $1 = "5" ]]; then
	./genpeter.py 3 s 0 > Table5/szymanski_3_fenced.c;
	./genpeter.py 4 s 0 > Table5/szymanski_4_fenced.c;
	./genpeter.py 5 s 0 > Table5/szymanski_5_fenced.c;
	./genpeter.py 6 s 0 > Table5/szymanski_6_fenced.c;
	./genpeter.py 7 s 0 > Table5/szymanski_7_fenced.c;
	echo Table5 done;		
fi