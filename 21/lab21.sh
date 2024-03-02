#!/bin/bash
if [[ "$1" == "?" ]]; then
	echo "1 parametr - suffix(rashirenie file\n 2 parametr - long(ves file)\n";
	echo "ukazivaya razmer vi zadaete dlinu dlya dopolneniya"
fi;
suffix="${1:-.txt}"
long="${2:-100}"
fname="${3:-ext$suffix}"
mapfile -t files < <(ls | grep -E "\\$suffix")
if [[ $fname == ext$suffix ]]; then
	$(fallocate -l 1 ext$suffix)
fi;
for file in "${files[@]}"; do
	dif=$(((((($long-$(stat --printf="%s" $file))/$(stat --printf="%s" $fname))) | bc)+1))
	if [[ "$3" != "$file" ]]; then
		for (( i = 1; i <= $dif; i++ ))
		do
		$(cat $fname >> $file)
		done
		$(truncate -s $long $file) 
	fi;
done
if [[ $fname == ext$suffix ]]; then
        $(rm ext$suffix)
fi;


