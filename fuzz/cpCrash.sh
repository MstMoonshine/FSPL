#!/bin/bash

if [ -d "$(pwd)/crashes" ]; then
	rm -rf $(pwd)/crashes;
fi
mkdir crashes;


if [ -d "$(pwd)/out/crashes" ]; then
	dir=$(pwd)/out/crashes;
	i=0;
	for crashFile in "$dir"/id*; do
	   	cp $crashFile ./crashes/$i.spl;
		echo "copying to $(pwd)/crashes/$i.spl";
		((i++));
	done;
else
	i=0;
	for fuzzers in $(ls out); do
		for crashFile in out/"$fuzzers"/crashes/id*; do
			cp $crashFile ./crashes/$i.spl;
			echo "copying to $(pwd)/crashes/$i.spl";
			((i++));
		done;
	done;
fi

