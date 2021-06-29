#!/bin/bash

if [ "$1" == "" ]; then
    echo "Usage: $(basename $0) ANGLE"
    exit 1
fi

readonly angle="$1"
readonly angleNNN=$(printf "%03d" $angle)
readonly algorithm="pathtracer"
readonly pngfile=img/image$angleNNN.png

time ../../build/./raytracer render -r $algorithm -n 10 -d 2 --scene demo.txt -v ang=$angle -w 640 -h 480 --output $pngfile
