#!/bin/bash
if [[ "$1" == "?" ]]; then
	echo "1 parametr - suffix(rashirenie file\n 2 parametr - long(ves file)\n";
	echo "ukazivaya razmer vi zadaete dlinu dlya dopolneniya"
fi;
suffix="${1:-.txt}"
long="${2:-100}"
mapfile -t files < <(ls | grep -E "\\$suffix")
$(fallocate -l 1 ext$suffix)
for file in "${files[@]}"; do
	dif=$(($long-$(stat --printf="%s" $file)))
	for (( i = 1; i <= $dif; i++ ))
	do
	$(cat ext$suffix >> $file)
	done
done
$(rm ext$suffix)
