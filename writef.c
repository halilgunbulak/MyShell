// C program to implement one side of FIFO
// This side writes first, then reads
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#define MAX 
int size_char(char *array){
    int a=0; 
   while(array[a]!='\0'){
          a++;
   }
   
    return a;
}

int strCompare(char *array,char *array2){
    int a=0; 
   int firstWordSize= size_char(array);
   int secondWordSize= size_char(array2);
   if(firstWordSize>secondWordSize || firstWordSize<secondWordSize){
         return 0;
   }
   for(int a=0;a<firstWordSize;a++){
    if(array[a]!=array2[a]){
             return 0;
    }
   }
    return 1;
}

int main(int argc, char *argv[])
{

   
        //find time 
    time_t rawtime;
    struct tm * timeinfo;
    //time (&rawtime);
    timeinfo = localtime (&rawtime);
    char *b=asctime(timeinfo);
    //pid value return type char for sprintf processing
    char buffer[200];
    
    sprintf(buffer, "{ Pid degeri: %d } { Ppid degeri:  %d }  {Current local time and date: : %s \n",getpid(), getppid(), b);

    printf("\n buffer:  %s",buffer); 
   int fd;
   int flagFilename=0;
   char *fileName="emptyFile";
   for(int i=0;i<argc;i++){
        //printf("argv i =%s",argv[i]);
        if(strcmp("-f", argv[i])==0){
            fileName=argv[i+1];
            flagFilename=1;
             sprintf(fileName,"%s.txt",fileName);
        }
    }
    
    FILE * shelfFile;

    if(flagFilename==0){
          shelfFile = fopen("empty.txt", "a+");
       
    }else{
         shelfFile = fopen(fileName, "a+");
    }
     
    
     //if file doesn't exist a+ create file
  
    //and if exist 
   
    fwrite(buffer, sizeof(char), size_char(buffer), shelfFile);
    fclose(shelfFile);

     return 0;
}
