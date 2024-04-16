#!/bin/bash

# Encoding Process
cd EncodingProcess

gcc -o 1ConvertImageToCSV 1ConvertImageToCSV.c
./1ConvertImageToCSV

gcc -o 2RunLengthEncoding 2RunLengthEncoding.c
./2RunLengthEncoding

gcc -o 3ConvertCSVToBinary 3ConvertCSVToBinary.c
./3ConvertCSVToBinary

cd ..

# Decoding Process
cd DecodingProcess

gcc -o 1ConvertBinaryToCSV 1ConvertBinaryToCSV.c
./1ConvertBinaryToCSV

gcc -o 2RunLengthDecoding 2RunLengthDecoding.c
./2RunLengthDecoding

gcc -o 3ConvertCSVToImage 3ConvertCSVToImage.c
./3ConvertCSVToImage

cd ..
