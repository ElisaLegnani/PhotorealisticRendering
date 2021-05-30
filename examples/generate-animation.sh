for angle in $(seq 0 359); do
    angleNNN=$(printf "%03d" $angle)
    ./generate-image.sh $angle
done

# -r 25: number of frames per second
ffmpeg -r 25 -f image2 -s 680x480 -i demo/image%03d.png -vcodec libx264 -pix_fmt yuv420p demo.mp4
