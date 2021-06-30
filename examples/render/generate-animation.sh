if [ "$1" == "" ]; then
    echo "Usage: $(basename $0) NUM_OF_CORES"
    exit 1
fi

readonly num_of_cores="$1"

parallel -j $num_of_cores ./generate-image.sh '{}' ::: $(seq 0 359)

# -r 25: number of frames per second
ffmpeg -r 25 -f image2 -s 680x480 -i img/image%03d.png -vcodec libx264 -pix_fmt yuv420p demo.mp4
