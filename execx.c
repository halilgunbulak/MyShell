#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
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
int strtoint( char* charnums)
{
 int number=0;
 int index=0;
 while(charnums[index])
 {
    if(('0'<=charnums[index]) && (charnums[index]<='9'))
    {

    if(!number)
        number= ( (int) charnums[index]) - 48;
    else
    {
        number = (number *= 10) + ((int) charnums[index] - 48);
    }
    index++;
         }
         else
         {
            number=-1;
            printf("\nGecersiz islem");
            break;
         }
 }
 return number;
}

int main(int argc, char *argv[])
{
    int i = 0;
    int repeat=0;
    for(int i=0;i<argc;i++){
        
        if(strcmp("-t", argv[i]) ==0){
            repeat= strtoint(argv[i+1]);
        }
    }

    
    int j,result = 0;
    while (i < repeat)
    {
         i++;
        int pide = fork(); // call fork
        if(pide==0){

                         if (strCompare("cat", argv[3]) == 1)
                        {   printf("cat:\n");
                             j = execv("/bin/cat", argv);
                        }else if(strCompare("bash", argv[3]) == 1){
                             j = execv("/bin/sh", argv);
                        }
                        else if(strCompare("ls", argv[3]) == 1){
                             j = execv("/bin/ls", argv);
                        }
                        else
                        {
                           j = execv(argv[3], argv);
                        }
                        // eğer hata varsa
                        if (i < 0)
                        {
                            printf("yanlis bir komut girdiniz\n");
                            exit(0); 
                        }   
        }
    }
    i=0;
       while (i < repeat)
    {    
        int pide = wait(NULL);// wait child finished progress
       // printf("Process %d is terminated.\n", pide);
        i++;
    }
     
    return result;
    
}