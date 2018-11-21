#!/bin/bash

i=0;
file="konfigok.txt"

cp ./judgesRR ./judges
while read -r line
do
	end="RR.txt"
	filename="$line$end"
	echo $filename
	if [ $((i%2)) -eq 0 ]; then exec > $filename 
	else /home/levente/Egyetem/SUMO_v2/sumo/bin/sumo $line
	fi
	let "i += 1"
done < $file

file2="konfigok.txt"
cp ./judgesMDDF ./judges
while read -r line
do
	end="MDDF.txt"
	filename="$line$end"
	echo $filename
	if [ $((i%2)) -eq 0 ]; then exec > $filename 
	else /home/levente/Egyetem/SUMO_v2/sumo/bin/sumo $line
	fi
	let "i += 1"
done < $file2
