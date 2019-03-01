Basic C code for reading in a BMP image, reading the header information,<br>
color table, and image data, then writing to a file.<br>
<br>
The source code contains an extremely verbose amount of comments to explain<br>
the reason for every step along the process.<br>
<br>
<b>Build:</b><br>
(from main directory)<br>
mkdir bin<br>
gcc src/bmpcopy.c -o bin/bmpcopy<br>
<br>
<b>Usage:</b><br>
bin/bmpcopy [Input File Path] [Output File Path]<br>
