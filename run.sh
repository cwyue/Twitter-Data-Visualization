#!/bin/bash

let a=0
for j in $(seq 1 10)
do
	let a=a+100
	
	./generate $a graph$j -h out$j 
        ./analysis graph${j}.txt
done

