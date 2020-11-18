#!/bin/sh

if [ -d "$DIRECTORY" ]; then
	record=fuzz_record$(date +"%T")
	mkdir $record
	mv ./out ./$record/
fi

mkdir out
afl-fuzz -i test -o out -f temp/fuzz.spl ../bin/splc @@
