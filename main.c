#include <stdbool.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdint.h>
#define BLOCKSIZE 512

typedef uint8_t BYTE;
bool footerFound=false;      			//to Check the footer

//to remember what has been found
//nothing has been found at this place
bool mp3Found=false;					
bool jpgFound=false;
bool pngFound=false;
bool pdfFound=false;

 void footerFoundOfFile(BYTE array[]){
 int i;
 	for(i=0;i<512;i++)
	 {
 		int place=i;
 		if(mp3Found==true){
 	
 		if(array[place]=='3' && array[place+1]=='D' && array[place+2]=='I')   //to check the end OF File of mp3 file 
 		{
 			printf("let's play some music\n\n\n");
 			system("PAUSE");
 		footerFound=true;    //if found then turn the found status on 
        return;              //Dont't do anything just return to the main process
		}
		}
	else if(jpgFound==true)
		{
		if(array[place]==0xFF && array[place+1]==0xD9 )   //to check the end OF File of jpg file 
 		{
 			printf("image is here\n\n\n");
 			system("PAUSE");
		 footerFound=true;    //if found then turn the found status on 
        return;              //Dont't do anything just return to the main process
		}
		}
		else if(pdfFound==true)
		{
		if(array[place]=='%' && array[place+1]=='%' && array[place+2]=='E' && array[place +3]=='O' && array[place +4]=='F')   //to check the end OF File of pdf file 
 		{
 			printf("hello pdf is here\n\n\n ");
 			system("PAUSE");
 		footerFound=true;    //if found then turn the found status on 
        return;              //Dont't do anything just return to the main process
		}
		}
 	
 }
 }
 
 main()
 {
 	SetConsoleTitle("Data Recovery");
 	
 	FILE *card;
	card=fopen("Allformat.iso","rb");
	if(card==NULL)
    {
        fprintf(stderr,"file couldn't open ");
        return 2;
    }
    
    BYTE block[BLOCKSIZE];
    char string[8];
    FILE *recoveredFile;
    int count=-1;
    while((fread(block,BLOCKSIZE,1,card))==1)
    {



    if(block[0]=='%' && block[1]=='P' && block[2]=='D' && block[3] =='F')
        {
        	printf("in the if of PDF file");
           if(count>=0)
           { 	
           	if(footerFound==false)     //when a new header is found and not footer is found then to close the file
            fclose(recoveredFile);
           }
            pdfFound =true;
            mp3Found=false;
            jpgFound=false;
            
            count++;
            footerFound=false;         //a new file encountered so initially the footer is not found

            sprintf(string,"%03i.pdf",count);
            recoveredFile=fopen(string,"wb");
            fwrite(block,BLOCKSIZE,1,recoveredFile);

        }
        else
    	 if(block[0]=='I' && block[1]=='D' && block[2]=='3' && (block[3]==2 || block[3]==3 || block[3]==4) && block[4]==0)
        {
           if(count>=0)
           {
           	
           	if(footerFound==false)     //when a new header is found and not footer is found then to close the file
            fclose(recoveredFile);
        
		   }
		    pdfFound =false;
            mp3Found=true;
            jpgFound=false;
		  
            count++;
            footerFound=false;         //a new file encountered so initially the footer is not found
            sprintf(string,"%03i.mp3",count);
            recoveredFile=fopen(string,"wb");
            
           fwrite(block,BLOCKSIZE,1,recoveredFile);
      

		}
        else

         if(block[0]==0xff && block[1]==0xd8 && block[2]==0xff && (block[3] & 0xf0)==0xe0)
        {
        	printf("hello image is here in while in\n\n\n ");
 			system("PAUSE");
           if(count>=0)
           { 	
           	if(footerFound==false)     //when a new header is found and not footer is found then to close the file
            fclose(recoveredFile);
           }
           pdfFound =false;
            mp3Found=false;
            jpgFound=true;
           
            count++;
            footerFound=false;         //a new file encountered so initially the footer is not found

            sprintf(string,"%03i.jpg",count);
            recoveredFile=fopen(string,"wb");
            fwrite(block,BLOCKSIZE,1,recoveredFile);

        }
		  else if(count>=0)
    {	
		footerFoundOfFile(block);      //To check the footer of the file
		
		/*IF FOOTER IS FOUND THEN 
		*JUST WRITE THOSE BYTES AND 
		*CLOSE THE FILE
		*/
    	 if(footerFound==true)
		   {
		  
			 fwrite(block,BLOCKSIZE,1,recoveredFile);
			fclose(recoveredFile);
			continue;			   	
		   }
		   else
			 {
			 fwrite(block,BLOCKSIZE,1,recoveredFile);
				footerFound=false;  
    }

    }
	}

    fclose(card);
    return 0;
}

