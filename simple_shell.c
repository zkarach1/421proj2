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
        
        char *buffer = (char *) malloc(bufferSize);
        character =getline(&buffer, bufferSize, stdin);
        printf()

        if (sizeof(gets(buffer)) >= bufferSize)
        {
            bufferSize = BUFFER + bufferSize;
            buffer = realloc(buffer, bufferSize);


        }

        buffer = gets(buffer);
        // //buffer1 = fgetc(stdin);
        // printf("here is buffer:");
        // printf("%c", buffer[0]);

        if (buffer != NULL)
        {
            //printf("%s",buffer);
            return buffer; 

        }   
        else if (ferror(stdin))
        {
            perror("Error in read line");
        }
    }
}   

char **tokenenizing(char *line)
{
    
    char delimit[] = " \t\r\n\v\f";
    char *token;
    char **token_array = (char **) malloc(bufferSize);
    int size_check = (sizeof(char *) * bufferSize);
    //printf(size_check);
    int count = 0;

    token = strtok(line, delimit);
    while(token != NULL)
    {
        //printf("%s", token);
        token_array[count]= token;
        count++;
        //check to make sure theres enough space
        if (count >= size_check)
            {
                bufferSize = BUFFER + bufferSize; 
                token_array = realloc(token_array, bufferSize * sizeof(char**));
                
                
            }

        token = strtok(NULL, delimit); 
        //printf("%s", token);

    }

    token_array[count] = NULL;
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

    do
    {
        printf("> ");
        //printf("here1");
        line = read_line();
        //printf("here2");
        tokens = tokenenizing(line);
        //printf("here3");
        status = starting_process(tokens);
        //printf("%s", *tokens);
        // free(line);
        // free(tokens);

    } while(status);

}

int main (int argc, char **argv)
{
    loop1(); 
}