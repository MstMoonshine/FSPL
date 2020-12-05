#!/bin/sh

DIRECTORY=$(pwd)/out
if [ -d "$DIRECTORY" ]; then
        record=pastOut/fuzz_record$(date +"%T")
        mkdir $record
        mv ./out ./$record/
fi

mkdir out
<<<<<<< HEAD
afl-fuzz -m 99999999 -i test -o out -f temp/fuzz0.spl ../bin/splc @@
=======
afl-fuzz -m 200 -i test -o out -f temp/fuzz0.spl ../bin/splc @@
>>>>>>> 0cd26b2f5ecab0a5dd5c866457f61f911a1f67d5
