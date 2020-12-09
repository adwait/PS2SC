rm -f $1/pcompiled/*

for f in $1/*.c; do ./cseq-feeder.py -i $f --ee 2 --rounds 1 --prom $2; done

rm -f $1/*.log
mv $1/_cs_*.c $1/pcompiled/
