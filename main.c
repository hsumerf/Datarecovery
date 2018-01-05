#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include<windows.h>
typedef uint8_t BYTE;
#define BLOCKSIZE 512
//typedef int integer;
int main(void)
{
	FILE *card;
	card=fopen("//.//D:","rb");
	if(card==NULL)
    {
        fprintf(stderr,"file couldn't open ");
        return 1;
    }
  
    BYTE block[BLOCKSIZE];
    char jpgString[8];
    FILE *img;
    int imageCount=-1;
    while((fread(block,BLOCKSIZE,1,card))==1)
    {

   

    if(block[0]==0xff && block[1]==0xd8 && block[2]==0xff && (block[3] & 0xf0)==0xe0)
	//if(block[0]==0x89 && block[1]==0x50 && block[2]==0x4E && block[3]==0x47)      
	  {
           if(imageCount>=0)
           {
              fclose(img);
           }
            imageCount++;
            sprintf(jpgString,"%03i.jpg",imageCount);
            img=fopen(jpgString,"wb");
            fwrite(block,BLOCKSIZE,1,img);

        }
    else if(imageCount>=0)
    {
        fwrite(block,BLOCKSIZE,1,img);
    }

    }
    fclose(img);
    fclose(card);
    return 0;
}
