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

	( time timeout -s 9 $3 cbmc compiled/$1 --unwind $2 --no-unwinding-assertions  2>> err.txt | grep 'VERIFICATION' ) &>> results.txt;

	echo >> results.txt
	echo $1 'done evaluating'
}

cd ds
echo $(date) > results.txt
echo >> results.txt
echo $(date) > err.txt
echo "------- RESULTS -------" >> results.txt

run_individual _cs_hehner_2.c 5 3600
run_individual _cs_hehner_3.c 5 3600
run_individual _cs_linuxrwlocks_2.c 2 3600
run_individual _cs_linuxrwlocks_3.c 2 3600
run_individual _cs_queue_safe_2.c 4 3600
run_individual _cs_queue_safe_3.c 4 3600
run_individual _cs_stack_safe.c 4 3600

sed -i -e 's/VERIFICATION FAILED/VERIFICATION COMPLETE - UNSAFE/g' results.txt
sed -i -e 's/VERIFICATION SUCCESSFUL/VERIFICATION COMPLETE - SAFE/g' results.txt

cd ..
