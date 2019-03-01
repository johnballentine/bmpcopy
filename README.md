Basic C code for reading in a BMP image, reading the header information,
color table, and image data, then writing to a file.

The source code contains an extremely verbose amount of comments to explain
the reason for every step along the process.

<b>Build:</b>
(from main directory)
mkdir bin
gcc src/bmpcopy.c -o bin/bmpcopy

<b>Usage:</b>
bin/bmpcopy [Input File Path] [Output File Path]
