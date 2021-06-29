#!/bin/bash

if [ "$1" == "" ]; then
    echo "Usage: $(basename $0) ANGLE"
    exit 1
fi

readonly angle="$1"
readonly angleNNN=$(printf "%03d" $angle)
readonly pngfile=img/image$angleNNN.png

time ../../build/./raytracer render --scene demo.txt --output $pngfile -v ang=$angle
