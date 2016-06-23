#!/bin/bash

loops=3
clients=1000

function write_to {
declare -a arr=( 
"show all"
"show av"
"show lo"
"set mac lo 00:00:00:00:00:00"
"set ip lo 127.0.0.1 255.255.255.0"
)

for  ((i=0; i<$loops; i++)) do
	for j in "${arr[@]}"
	do
		echo "$j"
		sleep 1
	done
done
sleep 3

echo "exit"
}

for  ((i=0; i<$clients; i++)) do
	sleep 1
	write_to | ./client &
done
