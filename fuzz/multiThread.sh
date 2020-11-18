#!/bin/sh

if [ -d "$DIRECTORY" ]; then
        record=fuzz_record$(date +"%T")
        mkdir $record
        mv ./out ./$record/
fi

mkdir out
screen -dmS fuzzer0 afl-fuzz -i test -o out -f temp/fuzz.spl -M fuzzer0 ../bin/splc @@
screen -dmS fuzzer1 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer1 ../bin/splc @@
screen -dmS fuzzer2 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer2 ../bin/splc @@
screen -dmS fuzzer3 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer3 ../bin/splc @@
screen -dmS fuzzer4 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer4 ../bin/splc @@
screen -dmS fuzzer5 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer5 ../bin/splc @@
screen -dmS fuzzer6 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer6 ../bin/splc @@
screen -dmS fuzzer7 afl-fuzz -i test -o out -f temp/fuzz.spl -S fuzzer7 ../bin/splc @@
