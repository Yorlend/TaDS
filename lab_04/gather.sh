#!/bin/bash

START=1
END=10
STEP=1
N=1

echo i,data_type,op_type,time > $1
for ((i=START;i<=END;i+=STEP)); do
    push_time=$(echo -e "5\n100\n0\n" | ./app.exe | tee -a out.txt | sed -n -r 's/^.*: (.*) нс/\1/p')
    echo $N,list,push,$push_time >> $1
    let N++
done

for ((i=START;i<=END;i+=STEP)); do
    push_low_time=$(echo -e "3\n100\n0\n" | ./app.exe | tee -a out.txt | sed -n -r 's/^.*: (.*) нс/\1/p')
    push_high_time=$(echo -e "4\n100\n0\n" | ./app.exe | tee -a out.txt | sed -n -r 's/^.*: (.*) нс/\1/p')
    echo $N,array,push_low,$push_low_time >> $1
    let N++
    echo $N,array,push_high,$push_high_time >> $1
    let N++
done

