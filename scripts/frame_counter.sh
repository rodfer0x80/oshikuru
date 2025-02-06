#!/bin/sh

set -e

if [ -z $1 ]; then
    echo "Usage: frame_counter.sh <image_path>"
    exit 1
fi

image_path="$1"

measures="$(exiftool "$image_path" | grep "Image Size" | awk '{print $4}')"
if [ -z "$measures" ]; then
    echo "Unable to determine image size for $image_path."
    exit 1
fi
echo "Image size: $measures"

width="$(echo "$measures" | cut -d'x' -f1)"
height="$(echo "$measures" | cut -d'x' -f2)"
if ! [ "$width" -eq "$width" ] 2>/dev/null || ! [ "$height" -eq "$height" ] 2>/dev/null; then
    echo "Invalid dimensions extracted. Ensure the image path is correct and exiftool is installed."
    exit 1
fi
echo "Width: $width"
echo "Height: $height"

frames=$((width / height))
echo "Number of frames in image: $frames"
