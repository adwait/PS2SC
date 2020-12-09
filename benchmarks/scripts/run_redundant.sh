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

cd redundant_co
echo $(date) > results.txt
echo >> results.txt
echo $(date) > err.txt
echo "------- RESULTS -------" >> results.txt

run_individual _cs_redundant_co_5.c 6 3600
run_individual _cs_redundant_co_10.c 11 3600
run_individual _cs_redundant_co_15.c 16 3600
run_individual _cs_redundant_co_20.c 21 3600
#run_individual _cs_redundant_co_50.c 51 3600

sed -i -e 's/VERIFICATION FAILED/VERIFICATION COMPLETE - UNSAFE/g' results.txt
sed -i -e 's/VERIFICATION SUCCESSFUL/VERIFICATION COMPLETE - SAFE/g' results.txt

cd ..
