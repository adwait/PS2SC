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

	( time timeout -s 9 $3 cbmc compiled/$1 --unwind $2 $4 2>> err.txt | grep 'VERIFICATION' ) &>> results.txt;

	echo >> results.txt
	echo $1 'done evaluating'
}

cd triangular

echo $(date) > results.txt
echo >> results.txt
echo $(date) > err.txt
echo "------- RESULTS -------" >> results.txt

run_individual _cs_triangular_2_safe.c 1 3600
run_individual _cs_triangular_2_unsafe.c 1 3600 --no-unwinding-assertions
run_individual _cs_triangular_3_safe.c 1 3600
run_individual _cs_triangular_3_unsafe.c 1 3600  --no-unwinding-assertions
run_individual _cs_triangular_4_safe.c 1 3600
run_individual _cs_triangular_4_unsafe.c 1 3600 --no-unwinding-assertions
run_individual _cs_triangular_5_safe.c 1 3600 
run_individual _cs_triangular_5_unsafe.c 1 3600 --no-unwinding-assertions

sed -i -e 's/VERIFICATION FAILED/VERIFICATION COMPLETE - UNSAFE/g' results.txt
sed -i -e 's/VERIFICATION SUCCESSFUL/VERIFICATION COMPLETE - SAFE/g' results.txt

cd ..
