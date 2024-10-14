# CS50 filters

This project was build based on [this execise](https://cs50.harvard.edu/x/2024/psets/4/filter/more/), it aims to apply filters on 24-bit uncompressed BMP 4.0 images.

## Filter types:
- greyscale
- edge detection
- blur
- reflection

## Requirements
Clang

## How to run
After compiling with `make filter`,  run with `./filter -<fst char of type of filter> <path of image> <product image name>`

Example: `./filter -g ./images/yard.bmp out.bmp`




