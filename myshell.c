// including libraries
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
//char array size return;
int size_char(char *array);
// two char array compare and if equal return 1 else 0
int strCompare(char *array,char *array2);
//char elemanı boş mu değil mi buna göre return vermekte boş ise 1 dolu ise 0 dönmektedir.
int charIsEmpty(char *str);
//girilen komutun var mı yok mu olduğunu kontrol etmektedir.Eğer girilen komut yoksa girilen komutta hata olduğunu ekrana basmakta
int cmdHandler(char **args, char **cmdList);
// gelen komuta göre programları çalıştıran komut.
void execTakenCommand(char **args, char **cmdList, int index);
// tüm shelli temizlemekte
void clearAllTerminal(void);
// parse string to words by using delimiter
void split(char *str, char **parsed, char *delim);
// remove character '\n' from stringW
void remove_newline_char(char *str);
int parameterError(char *cmd, char **args);
// control arguments of tekrar program
// if wrong parameter control
int controlTekrar(char **args);
// check that whether a string is a number
//if input any error or mistake return -1  if not return 0
int input(char *str);
//we call in execTakenCommand
int execArgsWith(char **args);

int main()
{
    char inputString[700] = {'\0'};                                                        //  input takeb by user max 700 element letter                                        
    char *commandList[8] = {"execx","writefde","cat", "clear", "exit","bash","ls",NULL}; // command list
    int i; 
    char *parsedArgs[200] = {NULL};                                                        // arguments of parsed string
    char *processes[200] = {NULL};  // contains processes splitted by "|"
    while (1)
    {
        // if valid input does not entered, continue taking input
        if (input(inputString))
            continue;

        split(inputString, processes, "|"); // split processes by "|"
        i = 0;                              // reset index
        // i st process is not NULL
        while (processes[i] != NULL)
        {
            split(processes[i], parsedArgs, " "); // split arguments by " "
            // if command is not found and arguments are not true
            if (cmdHandler(parsedArgs, commandList))
            {
                printf("yanlis bir komut girdiniz\n");
            }
            i++; // increase process index
        }
    }
    return 0;
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

int charIsEmpty(char *str)
{
    // str value is not null
    while (*str != '\0')
    {
        // if str value is not empty
        if (*str != ' ')
        {
            return 0; // False: it is not empty
        }
        str++; // increse str pointer
    }
    return 1; // True: str is empty
}
int size_char(char *array){
    int a=0; 
   while(array[a]!='\0'){
          a++;
   }
   
    return a;
}
int input(char *str)
{
    printf("\nmyshell>>");
    fgets(str, 1000, stdin); 
    remove_newline_char(str); 
    // if str is not empty
    if (!charIsEmpty(str))
    {
        return 0;
    }

    return -1; 
}

int cmdHandler(char **args, char **cmdList)
{
    int i,isFound = 0;       
    while (cmdList[i] != NULL)
    {
        if (strCompare(args[0], cmdList[i]) == 1)
        {
            isFound = 1; // founded
            break;
        }
        i++;
    }

    if (isFound)
    {
        // if wrong parameter is not netered for this command (args[0])
        if (!parameterError(args[0], args))
        {
            execTakenCommand(args, cmdList, i); // execute the program
        }
        else
        {
            return -1; // We have problem. It does not work succesfully
        }
    }

    // if command is found, return 0. It means no problem.
    // otherwise, return -1. It means that we have problem. It is an error
    return isFound ? 0 : -1;
}

void execTakenCommand(char **args, char **cmdList, int index)
{
    if (strCompare("exit", cmdList[index]) == 1) 
    {
        exit(0); // terminate myshell program
    }
    else if (strCompare("clear", cmdList[index]) == 1)
    {
        clearAllTerminal(); // clear Terminal
    }
    else    // Otherwise
    {
        execArgsWith(args);
    }
}

int execArgsWith(char **args)
{
                    int pid = fork(); // call fork and create child process
                    int i,result=0; 
                    if (pid == 0)
                    {
                        if (strCompare("cat", args[0]) == 1)
                        {   printf("cat:\n");
                            i = execv("/bin/cat", args);
                        }else if(strCompare("bash", args[0]) == 1){
                            i = execv("/bin/sh", args);
                        }
                        else if(strCompare("ls", args[0]) == 1){
                            i = execv("/bin/ls", args);
                        }
                        else if(strCompare("execx",args[0]) == 1){
                            i=execv("execx",args);
                        }
                        else
                        {
                            i = execv(args[0], args);
                        }
                        // eğer hata varsa
                        if (i < 0)
                        {
                            printf("yanlis bir komut girdiniz\n");
                            exit(0); 
                        }
                    }
                    else
                    {
                        wait(&i);             // waiting for child to terminate
                        result = WEXITSTATUS(i);
                    }    

    return result;
}
//this method taken by https://stackoverflow.com/questions/50915364/how-strsep-works-in-c like strsep logic 
void split(char *str, char **parsed, char *delim)
{
    int i = 0; // parsed isndex
    while ((parsed[i] = strsep(&str, delim)) != NULL)
    {
        if (charIsEmpty(parsed[i])) 
        {
            continue;
        }
        i++;
    }
}

void remove_newline_char(char *str)
{
    while (*str != '\0') // str is not null
    {
        if (*str == '\n') // str is newline character
        {
            *str = '\0'; // str assigned null character
            break;
        }
        str++; // increse str pointer
    }
}

void clearAllTerminal()
{     // this code taken geeks by Halil Gunbulak 
     // https://www.geeksforgeeks.org/making-linux-shell-c/
    printf("\033[H\033[J"); // clear console
   
}



int controlTekrar(char **args)
{
    int i = 0;              // argument index
    while (args[i] != NULL) // argument is not NULL
    {
        i++; // increse index
    }
    //3 den az ise exec x e gönderilen parametre -1 dönüyoruz
    if (i < 3) // min args
    {
        return -1; 
    }
    return 0; 
}
int parameterError(char *cmd, char **args)
{
    if (strCompare(cmd,"execx") == 1) // parameter Control
    {
        if (!controlTekrar(args)) // 
        {
         
        }else{
                 return -1;    // we have an error
        }
    }
    return 0; // no error
}

