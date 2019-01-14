// Alex Marlow        TCES 203         tested on Ubuntu 32-bit
// The fifth copy that is for the extra creddit, pixelates the image in a slighty mosaic fasion.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#define HEADER_SIZE 54


int main(void) {
    //variables that hold the file name and dimensions
    int hight;
    int width;
    char name[100];
    //scans for file name and dimensions
    printf("Enter the file name: ");
    scanf("%s" , &name[0]);
    strcat(name , ".bmp");
    printf("Enter hight and width (in pixels) : ");
    scanf("%d %d", &hight, &width);

    //Copies of original photo and new files for writing on
    FILE *infile = fopen(name, "rb");
    FILE *outfile1 = fopen("copy1.bmp", "wb");
    FILE *infile2 = fopen(name, "rb");
    FILE *outfile2 = fopen("copy2.bmp", "wb");
    FILE *infile3 = fopen(name, "rb");
    FILE *outfile3 = fopen("copy3.bmp", "wb");
    FILE *infile4 = fopen(name, "rb");
    FILE *outfile4 = fopen("copy4.bmp", "wb");
    FILE *infile5 = fopen(name, "rb");
    FILE *outfile5 = fopen("copy5.bmp", "wb");
    FILE *infile6 = fopen(name, "rb");
    //Arrays for holding the pictures
    char header[HEADER_SIZE];
    int s = 0;
    unsigned char **pixels1 = (unsigned char**) calloc(hight, sizeof(unsigned char*));
    for ( s = 0; s < hight; s++ )
    {
        pixels1[s] = (unsigned char*) calloc(width * 3, sizeof(unsigned char));
    }
    unsigned char **pixels3 = (unsigned char**) calloc(hight, sizeof(unsigned char*));
    for ( s = 0; s < hight; s++ )
    {
        pixels3[s] = (unsigned char*) calloc(width * 3, sizeof(unsigned char));
    }
    int c,r,x;


    //moving picture to array
    fread( header, 1 , HEADER_SIZE , infile);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels1[c][r], 1 , 1, infile);
        }
    }

    //nested loop that increases bringtness by 50 up to 255
    for( r = 0; r < hight; r++) {
         for ( c = 0; c < width * 3; c += 1) {
             int temp = pixels1[r][c];
                  if(temp < 205){
                      temp = temp + 50;
                  } else {
                      temp = 255;
                  }
             pixels1[r][c] = temp;
         }
    }
    //writing array to copy1
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile1);

    for(c = 0; c < hight; c++) {
        for(r = 0; r < width * 3;r++) {
            fwrite( &pixels1[c][r], sizeof(char)  , 1  ,  outfile1);

        }
    }

    fclose(outfile1);
    //writing original copy of photo on array
       float contrast_ratio = 1.8;

// float contrast_ratio = 2.9695;
    fread( header, 1 , HEADER_SIZE , infile2);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels1[c][r], 1 , 1, infile2);
        }
    }


    //nested loop that increases the contrast of the photo
    for( r = 0; r < hight; r++) {
         for ( c = 0; c < width * 3; c += 1) {
              int temp = pixels1[r][c];
              temp = ((contrast_ratio * (temp - 128)) + 128);
                  if(temp < 0){
                      temp = 0;
                  } else if(temp > 255) {
                      temp = 255;
                  }
             pixels1[r][c] = temp;
         }
    }

    //writing the array to copy2
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile2);

    for(c = 0; c < hight; c++) {
        for(r = 0; r < width * 3;r++) {
            fwrite( &pixels1[c][r], sizeof(char)  , 1  ,  outfile2);

        }
    }


    fclose(outfile2);

    //writing original copy of photo to array
    fread( header, 1 , HEADER_SIZE , infile3);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels1[c][r], 1 , 1, infile3);
        }
    }


    //nested loop that switches pixels positions to make the picture rotated 180 degrees
    for( r = 0; r < hight; r++) {
         for ( c = 0; c < width*3; c += 3) {
              pixels3[r][c] = pixels1[hight - r - 1][(width*3) - c - 3];
              pixels3[r][c + 1] = pixels1[hight - r - 1][(width*3) - c - 2	];
              pixels3[r][c + 2] = pixels1[hight - r - 1][(width*3) - c - 1];

         }
    }

    //writes array to file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile3);

    for(c = 0; c < hight; c++) {
        for(r = 0; r < width * 3;r++) {
            fwrite( &pixels3[c][r], sizeof(char)  , 1  ,  outfile3);

        }
    }

    fclose(outfile3);

    //writing original copy of photo to array
    fread( header, 1 , HEADER_SIZE , infile4);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels1[c][r], 1 , 1, infile4);
        }
    }

    //devides pixels quardinates b 2, making one smaller image in the right lower corner
    for( r = 0; r < hight; r += 2) {
         for ( c = 3; c < width * 3; c += 6) {
              pixels1[r/2][c/2 - 1] = pixels1[r][c+0];
              pixels1[r/2][c/2 + 0] = pixels1[r][c+1];
              pixels1[r/2][c/2 + 1] = pixels1[r][c+2];

         }
    }
    //copies smaller image to other 3 parts of the photo
    for( r = 0; r < hight/2; r++ ) {
         for ( c = 0; c < width*3/2; c++) {
             pixels1[r][c + width*3/2] = pixels1[r][c];
             pixels1[r + hight/2][c + width*3/2] = pixels1[r][c];
             pixels1[r + hight/2][c] = pixels1[r][c];

         }
    }


    //writes array to file
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile4);

    for(c = 0; c < hight; c++) {
        for(r = 0; r < width * 3;r++) {
            fwrite( &pixels1[c][r], sizeof(char)  , 1  ,  outfile4);

        }
    }

    fclose(outfile4);
    //writes clean copies of picture on both arrays
    fread( header, 1 , HEADER_SIZE , infile5);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels1[c][r], 1 , 1, infile5);
        }
    }



//    fread( pixels1, 1 , hight * width * 3 , infile5);

    fread( header, 1 , HEADER_SIZE , infile6);

    for( c = 0; c < hight; c++) {
        for( r = 0; r < width * 3; r++) {
        fread( &pixels3[c][r], 1 , 1, infile6);
        }
    }

    //loop does simelar procces to copy4, except the devide by 2 and copy to other 3 parts
    // is done individualy for ever 4x4 set of pixels
    for( r = 0; r < hight;) {
         int pass = 0;
         for ( c = 0; c < width * 3;) {
              if(r <= hight - 4 && c <= (width*3) - 12) {
                  for( x = 0; x < 3; x++) {
                      //making initial cube
                      pixels3[r][c + x] = pixels1[r + 1][c + 3 + x];
                      pixels3[r][c + 3 + x] = pixels1[r + 1][c + 9 + x];
                      pixels3[r + 1][c + x] = pixels1[r + 3][c + 9 + x];
                      pixels3[r + 1][c + 3 + x] = pixels1[r + 3][c + 9 + x];

                  }
                  for( x = 0; x < 6; x++) {
                      //copying right
                      pixels3[r][c + 6 + x] = pixels3[r][c + x];
                      pixels3[r + 1][c + 6 + x] = pixels3[r + 1][c + x];

                  }
                  for( x = 0; x < 12; x++) {
                      //copying down
                      pixels3[r + 2][c + x] = pixels3[r][c + x];
                      pixels3[r + 3][c + x] = pixels3[r + 1][c + x];

                  }
                  c = (c+12);
                  pass = 1;
              //case for when there is a 3x3 and not a 4x4 set of pixels
              } else if( r <= hight - 3 && c <= (width*3) - 9 && pass == 0) {
                  for( x = 0; x < 3; x++){
                      pixels3[r][c + x] = pixels1[r + 2][c + 3 + x];
                      pixels3[r][c + 6 + x] = pixels1[r + 2][c + 3 + x];
                      pixels3[r + 2][c + x] = pixels1[r + 2][c + 3 + x];
                      pixels3[r + 2][c + 6 + x] = pixels1[r + 2][c + 3 + x];
                      pixels3[r][c + 3 + x] = pixels1[r + 2][c + 6 + x];
                      pixels3[r + 2][c + 3 + x] = pixels1[r + 2][c + 6 + x];
                      pixels3[r + 1][c + x] = pixels1[r + 1][c + 3 + x];
                      pixels3[r + 1][c + 6 + x] = pixels1[r + 1][c + 3 + x];
                      pixels3[r + 1][c + 3 + x] = pixels1[r + 1][c + 6 + x];

                  }
                  c = (c+9);
              } else {
              c++;
              }
         }
         //'if' statements that continue the program if a situation where less
         // than a 3x3 pixel set is available
         if (pass == 1) {
         r = (r + 4);
         } else if(pass == 0) {
         r = (r + 3);
         } else {
         r++;
         }
    }

    //writes file to copy5
    fwrite( header, sizeof(char)  , HEADER_SIZE  ,  outfile5);

    for(c = 0; c < hight; c++) {
        for(r = 0; r < width * 3;r++) {
            fwrite( &pixels3[c][r], sizeof(char)  , 1  ,  outfile5);

        }
    }

    fclose(outfile5);

    fclose(infile);
    //conferms photos have been created and terminates program
    printf("Done. Check the generated imeges.\n");

    return 0;

}
