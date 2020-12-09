#!/bin/bash

function run_tests {
	echo $(date) > $1/results.txt 
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

	sed -i -e 's/VERIFICATION FAILED/VERIFICATION COMPLETE - UNSAFE/g' $1/results.txt;
	sed -i -e 's/VERIFICATION SUCCESSFUL/VERIFICATION COMPLETE - SAFE/g' $1/results.txt;
}

if [[ $1 = "all" ]]; then 
run_tests mutex/Table1 2 3600

run_tests mutex/Table2/2a 1 3600

run_tests mutex/Table2/2b 1 3600

run_tests mutex/Table3 1 3600

run_tests mutex/Table4 1 3600

run_tests mutex/Table5 1 3600

run_tests mutex/Table6 1 3600

run_tests mutex/Table7 2 3600

run_tests mutex/Table8 4 3600

else

run_tests $1 $2 $3;

fi
