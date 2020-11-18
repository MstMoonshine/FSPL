#!/bin/sh

DIRECTORY=$(pwd)/out
if [ -d "$DIRECTORY" ]; then
        record=pastOut/fuzz_record$(date +"%T")
        mkdir $record
        mv ./out ./$record/
fi

mkdir out
afl-fuzz -m none -i test -o out -f temp/fuzz0.spl ../bin/splc @@