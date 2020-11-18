#!/bin/sh

DIRECTORY=$(pwd)/out
if [ -d "$DIRECTORY" ]; then
        record=pastOut/fuzz_record$(date +"%T")
        mkdir $record
        mv ./out ./$record/
fi

mkdir out
screen -dmS fuzzer0 afl-fuzz -m none -i test -o out -f temp/fuzz0.spl -M fuzzer0 ../bin/splc @@
screen -dmS fuzzer1 afl-fuzz -m none -i test -o out -f temp/fuzz1.spl -S fuzzer1 ../bin/splc @@
screen -dmS fuzzer2 afl-fuzz -m none -i test -o out -f temp/fuzz2.spl -S fuzzer2 ../bin/splc @@
screen -dmS fuzzer3 afl-fuzz -m none -i test -o out -f temp/fuzz3.spl -S fuzzer3 ../bin/splc @@
screen -dmS fuzzer4 afl-fuzz -m none -i test -o out -f temp/fuzz4.spl -S fuzzer4 ../bin/splc @@
screen -dmS fuzzer5 afl-fuzz -m none -i test -o out -f temp/fuzz5.spl -S fuzzer5 ../bin/splc @@
screen -dmS fuzzer6 afl-fuzz -m none -i test -o out -f temp/fuzz6.spl -S fuzzer6 ../bin/splc @@
screen -dmS fuzzer7 afl-fuzz -m none -i test -o out -f temp/fuzz7.spl -S fuzzer7 ../bin/splc @@
