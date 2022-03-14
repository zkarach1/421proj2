#define BUFFER 1024
int bufferSize = BUFFER;
//hello
#include <stdio.h>
#include <stdlib.h> 
#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>

//returning a pointer
char *read_line(void)
{
    while(1)
    {
        size_t bufsize = 32;
        char *buffer = (char *) malloc(bufsize * sizeof(char));

        
        //printf("%zu", character);
        //printf("%s", buffer);

        //check for empty buffer
        getline(&buffer, &bufsize, stdin);

        char c = buffer[0];
        //if its the end of the file just return null buffer
        if (c == EOF || c == '\n')
        {
            printf("in here");
            buffer[0] = '\n';
            return buffer; 

        }


        //getline(&buffer, &bufsize, stdin);
        //getline automatically realocated space so no need to do it our self
        if (buffer != NULL)
        {

            return buffer; 

        }   
        
        if (ferror(stdin))
        {
            perror("Error in read line");
        }
    }

}   

char **tokenenizing(char *line)
{

    char delimit[] = " \t\r\n\v\f";
    char *token;
    char **token_array = malloc(bufferSize * sizeof(char**));
    int i  =0;
    int count = 0;

    //gonna make a copy of the string to 
    char *line2 = (char*)malloc(strlen(line));
    strcpy(line2,line);

    if( strtok(line2, delimit) != NULL)
    {
        count++;
        while( strtok(NULL," \t") != NULL )
            count++;
    }

    //printf("this many counts");
    //printf("%d", count);

    if (count >= bufferSize)
    {
        bufferSize = BUFFER + bufferSize; 
        token_array = realloc(token_array, bufferSize * sizeof(char**));
    }

    token = strtok(line, delimit);
    
    while (token!=NULL)
    {
            token_array[i]= token;
            //printf("here is token in array: ");
            //printf("%s", token_array[i]);
            i++;
            token = strtok(NULL, delimit); 

    }
  

    token_array[i] = NULL;
    return token_array; 


}


///LAUNCHING


int starting_process(char **tokens)
{

    int child_status; 
    pid_t child_pid;
    pid_t wait_pid;


    char str1[] = "exit"; 
    char str2[] = "Exit";

    //check for exit

    if(tokens == NULL )
    {

        return 1;

    }

    if (tokens[0] != NULL)
    {
        int check1 = strcmp(tokens[0], str1);
        int check2 = strcmp(tokens[0], str2);
        if ((check1 == 0) || check2 == 0 )
        {
            free(tokens);
            exit(0); 
        }


    }

    //check for proc
    char str3[] = "proc";
    int check3 = strcmp(tokens[0], str3);

    if (check3 == 0)
    {
    
        //check to make sure there is an argument with proc
        if (tokens[1] == NULL)
        {
            printf("no argument given \n");
            return 1;
        }

        //check if more than one argument was given

        if (tokens[2]!= NULL)
        {
            printf("too many arguments were given with proc \n");
            return 1;
        }

        


        //if argument is given build file path
        //string manipulation,how to change a string in c 

        //how to open file in c 
        //how to read from file from c
        //printf("herenow");
        //printf("%s", tokens[1]);
        char *string = "/proc/";
        //printf("herenow");
        
        size_t len1 = strlen(string);
        size_t len2 = strlen(tokens[1]);
        char *result = malloc(len1 +len2 +1);
        memcpy(result, string, len1);
        memcpy(result + len1, tokens[1], len2 + 1);
        printf("%s", result);

        //open file
        //strcat(string,tokens[1]);
        //printf("%s", string);

        return 1; 
            // char *array[2]; 
            // char string[2];
            // array[0] = '/proc/';
            // array[1]= tokens[1];

            // strncpy(string,array,2);
            // printf("%s", string);




        




    }



//running arguments
    child_pid = fork();
    if (child_pid == 0)
    {
        int status_code = execvp(tokens[0], tokens);

        if (status_code == -1)
        {
            printf("terminated incorrectly");
            

        }

        return 0;


    }

    else
    {
       do
       {
        //printf("here");
        wait_pid = wait(&child_status);

       }while (wait_pid != child_pid);

       


    }

    return 1;
    

}




void loop1(void)
{
    char *line;
    char **tokens;
    int status;

    do
    {
        printf("> ");
        line = read_line();
        tokens = tokenenizing(line);
        status = starting_process(tokens);
        free(line);
        free(tokens);

    } while(status);

}

int main ()
{
    loop1(); 
}