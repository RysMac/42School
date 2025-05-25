#!/bin/bash

FILES=("10-2" "10-70" "20-60" "42" "50-4" "100-6"
		"basictest" "cube" "elem-col" "elem-fract"
		"elem" "elem2" "julia" "mars"
		"pentenegpos" "plat" "pnp_flat" "pylone"
		"pyra" "pyramide" "t1" "t2")

for file in "${FILES[@]}"; do
	echo "Launching: $file"
	./fdf "$file"
	echo "Closed: $file"
done
