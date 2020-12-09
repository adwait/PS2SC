#!/bin/bash

# Compilation script for the tool PSChecker

# Compile chosen table(s) with hardcoded parameters

tooldir=.
relpath=benchmarks

function compile_table {
	rm -f $1/compiled/*

	echo $(date) > $1/compilelog
	echo >> $1/compilelog
	echo Compiling $1 >> $1/compilelog
	echo >> $1/compilelog
	echo ---- params used --- >> $1/compilelog
	echo "ee	" $2 >> $1/compilelog
	echo "rounds	" $3 >> $1/compilelog
	echo "prom	" $4 >> $1/compilelog
	echo >> $1/compilelog

	cd ..

	for f in $relpath/$1/*.c; do
		./cseq-feeder.py -i $f --ee $2 --rounds $3 --prom $4 >> $relpath/$1/compilelog; 
		echo $f done;
	done

	cd $relpath/

	rm -f $1/*.log
	mv $1/_cs_*.c $1/compiled/
	echo $1 done
	
}

function compile_individual {
	
	# echo > $1/compilelog$5
	# echo $(date) >> $1/compilelog$5
	# echo >> $1/compilelog$5
	# echo Compiling $1 >> $1/compilelog$5
	# echo >> $1/compilelog$5
	# echo ---- params used --- >> $1/compilelog$5
	# echo "ee	" $2 >> $1/compilelog$5
	# echo "rounds	" $3 >> $1/compilelog$5
	# echo "prom	" $4 >> $1/compilelog$5
	# echo >> $1/compilelog$5

	cd ..

	if [[ "$#" -eq 5 ]]; then
		./cseq-feeder.py -i $relpath/$1/$5 --ee $2 --rounds $3 --prom $4; 
	elif [[ "$#" -eq 6 ]]; then
		./cseq-feeder.py -i $relpath/$1/$5 --eprom $6 --ee $2 --rounds $3 --prom $4; 
	fi

	cd $relpath/

	mv $1/_cs_*.c $1/compiled/	
	echo $5 done;
}

if [[ $1 = "mutex" ]]; then
	
	compile_table $tooldir/mutex/Table1 4 1 0;
	compile_table $tooldir/mutex/Table2/2a 6 1 0;
	compile_table $tooldir/mutex/Table2/2b 2 1 0;
	compile_table $tooldir/mutex/Table3 2 1 0;
	compile_table $tooldir/mutex/Table4 2 1 0;
	compile_table $tooldir/mutex/Table5 2 1 0;
	compile_table $tooldir/mutex/Table6 2 1 0;
	compile_table $tooldir/mutex/Table7 2 1 0;
	compile_table $tooldir/mutex/Table8 4 2 0;

elif [[ $1 = "exppromT" ]]; then
	compile_individual $tooldir/exponential_promiseT 10 4 1 promised_exponential_1.c t;
	compile_individual $tooldir/exponential_promiseT 12 5 1 promised_exponential_2.c t;
elif [[ $1 = "exppromT2" ]]; then
	compile_individual $tooldir/exponential_promiseT2 10 4 1 promised_exponential_1.c t2;
	compile_individual $tooldir/exponential_promiseT2 12 5 1 promised_exponential_2.c t2;
elif [[ $1 = "fibpromT" ]]; then
	compile_individual $tooldir/fibonacci_promiseT 8 4 1 promised_fibonacci_2.c t;
	compile_individual $tooldir/fibonacci_promiseT 10 5 1 promised_fibonacci_3.c t;
	compile_individual $tooldir/fibonacci_promiseT 12 6 1 promised_fibonacci_4.c t;
elif [[ $1 = "fibpromT2" ]]; then
	compile_individual $tooldir/fibonacci_promiseT2 8 4 1 promised_fibonacci_2.c t2;
	compile_individual $tooldir/fibonacci_promiseT2 10 5 1 promised_fibonacci_3.c t2;
	compile_individual $tooldir/fibonacci_promiseT2 12 6 1 promised_fibonacci_4.c t2;
elif [[ $1 = "tripromT" ]]; then
	compile_individual $tooldir/triangular_promiseT 8 4 1 promised_triangular_2.c t;
	compile_individual $tooldir/triangular_promiseT 10 5 1 promised_triangular_3.c t;
	compile_individual $tooldir/triangular_promiseT 12 6 1 promised_triangular_4.c t;
elif [[ $1 = "tripromT2" ]]; then
	compile_individual $tooldir/triangular_promiseT2 8 4 1 promised_triangular_2.c t2;
	compile_individual $tooldir/triangular_promiseT2 10 5 1 promised_triangular_3.c t2;
	compile_individual $tooldir/triangular_promiseT2 12 6 1 promised_triangular_4.c t2;
elif [[ $1 = "fibonacciU" ]]; then
	compile_table $tooldir/fibonacci_unsafe 20 4 0;
elif [[ $1 = "fibonacci" ]]; then
	compile_table $tooldir/fibonacci 20 4 0;
elif [[ $1 = "exponential" ]]; then
	compile_table $tooldir/exponential 10 2 0;
elif [[ $1 = "redundant_co" ]]; then
	compile_table $tooldir/redundant_co 5 2 0;
elif [[ $1 = "rw" ]]; then
	compile_table $tooldir/rw 5 2 0;
elif [[ $1 = "controlflow" ]]; then
	compile_table $tooldir/controlflow 10 2 0;
elif [[ $1 = "ds" ]]; then
	compile_table $tooldir/ds 4 1 0;
elif [[ $1 = "triangular" ]]; then
	compile_table $tooldir/triangular 10 3 0;
else
	compile_table $tooldir/$1 $2 $3 $4;
fi

