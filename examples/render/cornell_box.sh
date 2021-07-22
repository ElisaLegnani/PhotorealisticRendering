    echo ""
    echo "Usage: ./$(basename $0) NUM_OF_CORES <n_rays> <depth> <samples> <width> <height> <a-factor>"
        echo ""
    echo "NOTE: Default values are set to produce quickly a small approximate image of the cornell box, you are welcome to increase values as you wish, always taking in mind that the runtime increses as well."
    echo ""
    
if [ "$1" == "" ]; then
    echo "  Error: indicate NUM_OF_CORES"
    echo ""
    exit 1
fi

readonly num_of_cores="$1"
readonly n_rays="${2:-2}"
readonly depth="${3:-2}"
readonly samples="${4:-16}"
readonly width="${5:-200}"
readonly height="${6:-200}"
readonly a_factor="${7:-0.6}"
readonly output="cb_n${n_rays}_d${depth}_s${samples}_w${width}_h${height}_a${a_factor}.png"

#parallel -j $num_of_cores ./generate-image.sh '{}' ::: $(seq 0 359) ::: ${2:-1}

parallel -j $num_of_cores ../../build/./raytracer '{}' ::: render ::: cornell_box.txt ::: -n ::: $n_rays ::: -d ::: $depth ::: --samples ::: $samples ::: -h ::: $height ::: -w ::: $width ::: --a_r ::: $a_factor ::: --output ::: $output
