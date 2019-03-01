/**

Simple bitmap read and write.

This program simple reads in an image and writes it to a new file.
It is used to understand bitmap reading and writing every step of the way.

The comments are as verbose as possible to explain in the maximum amount of detail
the purpose of each step of the process.

**/

#include <stdio.h>
#include <stdlib.h>

int main( int argc, char * argv[] )
{
   // Handle input file and output file arguments.
   if ( argc != 3 ) {
      // argc is the number of arguments, argv is the array of arguments.
      // the first argument is always the program name itself.
      printf("Incorrect number of arguments.\nUsage: bmpcopy [input path] [output path]\n");
      exit(1000);
   }

    ///////////// Open file for read and file for write. /////////////

    FILE *infile = fopen(argv[1],"rb");
    FILE *outfile = fopen(argv[2],"wb");
    // rb and wb are used to read binary files.  Sometimes non-unix systems
    // require it, as w or b will be read in as text.

    if(infile == NULL){ // Check if file open was successful
        printf("File cannot be opened.\n");
    }

    ///////////// Read the image /////////////

    // unsigned chars have a value of between 0 and 255
    unsigned char header[54];
    unsigned char color_table[1024];

    // Read BMP header into header array.
    for(int i = 0; i<54; i++){
        header[i] = getc(infile); // getc is get single character
    }

    /**
    Bitmap Image Format:

           Image                   BMP
    -------------------    -------------------
    |   Image Header  |    |   54 Bytes      |
    |   Color Table   |    |   1024 Bytes    |
    |   Image Data    |    |   Image Data    |
    -------------------    -------------------

    Bitmap often uses "indexed color".  There is a lookup table with a limited number of colors.  In this case,
    it is referred to as the "color table".

    Info about BMP headers:
    http://www.ece.ualberta.ca/~elliott/ee552/studentAppNotes/2003_w/misc/bmp_file_format/bmp_file_format.htm

    Offsets:
    The "h" represents the end of the number.  So offset 0012h would be 18 in decimal, as 12 in hex is 18 in decimal.
    Similarly, 001Ch would be offset 28, as 1C is 28 in decimal.  We use the decimal value to access our array.

    **/

    // Store width, height, and bit depth from the header array.
    int width = *(int *)&header[18]; // The header array is an array of chars, so we need to cast the values and store them as ints.
    int height = *(int *)&header[22];

    /** "In uncompressed BMP files, and many other bitmap file formats, image pixels are
    stored with a color depth of 1, 4, 8, 16, 24, or 32 bits per pixel (BPP). Images of
    8 bits and fewer can be either grayscale or indexed color."
    Source: http://www.di.unito.it/~marcog/SM/BMPformat-Wiki.pdf
    **/

    int bit_depth = *(int *)&header[28];

    // Not all bitmaps have a color table, only indexed color images.  We need to check before we read in the color table.
    if (bit_depth <= 8){ // If the image is either grayscale or indexed color.
        fread(color_table, sizeof(unsigned char), 1024, infile); // Read in color table into our color_table array.
        /** We use sizeof(unsigned char) because the fread function requires a "size_t" type which sizeof returns.
            fread documentation:
            https://www.tutorialspoint.com/c_standard_library/c_function_fread.htm
            fread(Pointer to block of memory that can fit everything,
                  size (in bytes) of each element to be read,
                  number of elements,
                  a pointer to a FILE object that specifies the input stream)
        **/
    }

    ///////////// Write the image /////////////

    fwrite(header, sizeof(unsigned char), 54, outfile); // Write header to file first

    // Create a buffer in memory to store the image data (actual pixels).
    // The buffer needs to store all pixels.  The total number of pixels is given by the width * the height.
    unsigned char buffer[height * width];

    fread(buffer, sizeof(unsigned char), (height * width), infile); // read actual pixel data into buffer

    // Check if the color table exists, because we'll need to write it to the file if it does.
    if (bit_depth <= 8){
        fwrite(color_table, sizeof(unsigned char), 1024, outfile); // Write the color table to the file next
    }

    // Now, we can write the pixel data to our output image.
    fwrite(buffer, sizeof(unsigned char), (height * width), outfile);

    // Now we can close both files.
    fclose(infile);
    fclose(outfile);

    // Notify the user that it was successful and print some information.
    printf("Copy successful!\n");
    printf("Width: %d\n", width);
    printf("Height: %d\n", height);

    return 0;
}
