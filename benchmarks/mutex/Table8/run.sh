echo "RESULTS" > results.txt
echo "" >> results.txt

for f in  compiled/*.c ;
do

g=${f#compiled/_cs_} 
g=${g%.c*}

echo $g
echo $g >> results.txt
echo "" >> results.txt

(time timeout -s 9  ${1}s cbmc  $f --unwind 4 --stop-on-fail --verbosity 5 > compiled/${g}.out  2>err.txt) &>> results.txt

echo "" >> results.txt
echo "" >> results.txt
echo "" >> results.txt
done

grep "FAILED" compiled/*
grep "SUCCESSFUL" compiled/*


