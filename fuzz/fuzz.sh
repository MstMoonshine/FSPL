#!/bin/sh

record=fuzz_record$(date +"%T")
mkdir $record
mv ./out ./$record/

mkdir out
#screen -S fuzzer afl-fuzz -i test -o out -f temp/fuzz.spl ../bin/splc @@
afl-fuzz -i test -o out -f temp/fuzz.spl ../bin/splc @@
