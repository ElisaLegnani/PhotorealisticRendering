#!/bin/bash

    echo ""
    echo "Usage: ./$(basename $0) NUM_OF_CORES <angle> <width> <height> <output_filename> <a-factor> <samples> <n_rays> <depth>"
        echo ""
    
if [ "$1" == "" ]; then
    echo "  Error: indicate NUM_OF_CORES"
    echo ""
    exit 1
fi

readonly num_of_cores="$1"
readonly angle="${2:-0}"
readonly width="${3:-640}"
readonly height="${4:-480}"
readonly output="${5:-image.png}"
readonly a_factor="${6:-1}"
readonly samples="${7:-0}"
readonly n_rays="${8:-10}"
readonly depth="${9:-2}"

parallel -j $num_of_cores ../../build/./raytracer '{}' ::: render ::: image.txt ::: -n ::: $n_rays ::: -d ::: $depth ::: --samples ::: $samples ::: -h ::: $height ::: -w ::: $width ::: --a_r ::: $a_factor ::: --output ::: $output ::: -v ::: ang=$angle
