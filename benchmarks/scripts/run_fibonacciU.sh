#!/bin/bash

function run_tests {
	echo $(date) > $1/results.txt;
	echo >> $1/results.txt
	echo Evaluating $1 >> $1/results.txt
	echo >> $1/results.txt
	echo ---- params --- >> $1/results.txt 
	echo "L	" $2 >> $1/results.txt
	echo "timeout	" >> $1/results.txt
	echo >> $1/results.txt
	echo >> $1/results.txt

	echo "------- RESULTS -------" >> $1/results.txt

	for f in $1/compiled/*.c;
	do
		echo >> $1/results.txt
		echo $f >> $1/results.txt;
		( time timeout -s 9 $3 cbmc $f --unwind $2 --no-unwinding-assertions 2> $1/err.txt | grep 'VERIFICATION' ) &>> $1/results.txt;
		echo '' >> $1/results.txt;
		
		echo $f 'done evaluating';
	done
}

function run_individual {
	echo >> results.txt
	echo Evaluating $1 >> results.txt
	echo >> results.txt
	echo ---- params --- >> results.txt 
	echo "L	" $2 >> results.txt
	echo "timeout	" $3 >> results.txt
	echo >> results.txt

	( time timeout -s 9 $3 cbmc compiled/$1 --unwind $2 2>> err.txt | grep 'VERIFICATION' ) &>> results.txt;

	echo >> results.txt
	echo $1 'done evaluating'
}

cd fibonacci_unsafe
echo $(date) > results.txt
echo >> results.txt
echo $(date) > err.txt
echo "------- RESULTS -------" >> results.txt

run_individual _cs_fibonacci_2.c 10 3600
run_individual _cs_fibonacci_3.c 10 3600
run_individual _cs_fibonacci_4.c 15 3600

sed -i -e 's/VERIFICATION FAILED/VERIFICATION COMPLETE - UNSAFE/g' results.txt
sed -i -e 's/VERIFICATION SUCCESSFUL/VERIFICATION COMPLETE - SAFE/g' results.txt

cd ..