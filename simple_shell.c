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
            //printf("in here");
            buffer = NULL;
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

    int check1 = strcmp(tokens[0], str1);
    int check2 = strcmp(tokens[0], str2);

    if(tokens[0] == NULL)
    {

        return 1;
    }

    if ((check1 == 0) || check2 == 0 )
    {
        //need to free all memory
        exit(0); 
    }


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

    // do
    // {
        printf("> ");
        //printf("here1");
        line = read_line();
        //printf("here is the buffer:");
        //printf("%s", line);
        tokens = tokenenizing(line);
        //status = starting_process(tokens);
        // free(tokens);

    // } while(status);

}

int main (int argc, char **argv)
{
    loop1(); 
}