#!/bin/bash

echo N,selection,merge,key_selection,key_merge > $1

for ((i=100;i<2000;i+=100));
do
    python datagen.py $i > .tmp_data.txt

    sel_time=$(echo -e "1\n1\n0\n" | ./app.exe .tmp_data.txt | sed -n -r 's/^.*time: (.*)us/\1/p')
    mer_time=$(echo -e "1\n2\n0\n" | ./app.exe .tmp_data.txt | sed -n -r 's/^.*time: (.*)us/\1/p')
    sel_key_time=$(echo -e "2\n1\n0\n" | ./app.exe .tmp_data.txt | sed -n -r 's/^.*time: (.*)us/\1/p')
    mer_key_time=$(echo -e "2\n2\n0\n" | ./app.exe .tmp_data.txt | sed -n -r 's/^.*time: (.*)us/\1/p')

    echo $i,$sel_time,$mer_time,$sel_key_time,$mer_key_time >> $1
done

rm .tmp_data.txt
