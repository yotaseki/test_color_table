#/bin/bash
for a in `seq -w 0 100`
do
    mkdir -p $2/thre${a}
done
./detectUsingFCN.py $1 $2
