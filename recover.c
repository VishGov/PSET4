/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

#define CARD "card.raw"

int main()
{
    //	open card.raw.
    FILE* card = fopen(CARD,"r");

    // initialise index for jpeg file number.
        int file_num = 0;

    //	check if it is empty of if any error occurs.
    if(card == NULL)
    {
    	printf("ERROR\n");
    	return 1;

    }
    //	if not, continue.
    else
    {
		//  initialise a file.
        FILE* jpeg = fopen("000.jpg","w");

        
        while(!feof(card))
		{
            //  assign an array of 512 bytes to store the read block size.
            char* buffer = malloc(512);

            //  read 512 byte block into buffer.
            fread(buffer, 512, 1, card);

            //  check the starting bytes of block for JPEG starting bytes.
            if(  buffer[0] == (char)0xff && buffer[1] == (char)0xd8 && buffer[2]  == (char)0xff && ( buffer[3] == (char)0xe0 || buffer[3] == (char)0xe1) )
            {
                    // close previous file.
                    fclose(jpeg);

                    // open new jpeg file to write into. 
                    char filename[sizeof ("000.jpg")];
                    if(file_num < 10)
                        sprintf(filename,"00%d.jpg",file_num);
                    else
                        sprintf(filename,"0%d.jpg",file_num);

                    jpeg = fopen(filename,"w");
            
                    //  increase file number for the next file.
                    file_num++; 

            }
            
            //  write to the opened jpeg.
            fwrite(buffer, 512, 1, jpeg);

            //  free current buffer to take in next block.
  	    	free(buffer);
	  	
		}
        //  close the last jpeg when end of file reached.
        fclose(jpeg);		
    	
    }
    //  close card.raw.
    fclose(card);

    return 0;
}
