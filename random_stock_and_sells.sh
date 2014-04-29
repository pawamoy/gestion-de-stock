#!/bin/bash

ref() {
	echo -n "$(< /dev/urandom tr -dc 0-9 | head -c8) "
}

qty() {
	echo -n "$(($RANDOM%1000)) "
}

buy() {
	echo $(($RANDOM%200))
}

sell() {
	echo $(($RANDOM%200))
}

prices() {
	local b=$(buy)
	local s=$(sell)
	let s+=$b
	echo -n "$b $s "
}

discount() {
	echo -n "$(($RANDOM%101)) "
}

date() {
	echo "2013 $(($RANDOM%13)) $(($RANDOM%29)) "
}

generate_stock_article() {
	ref; qty; prices; echo -n "0 "; date
}

generate_sold_article() {
	echo -n "$(generate_stock_article)"; date
}

generate_stock() {
	for ((i=0; i<300; i++)); do
		generate_stock_article
	done
}

generate_sells() {
	for ((i=0; i<100; i++)); do
		generate_sold_article
	done
}

[ $# -lt 2 ] && { echo "usage: $0 stock_file sells_file"; exit 1; }

generate_stock > "$1"
generate_sells > "$2"
