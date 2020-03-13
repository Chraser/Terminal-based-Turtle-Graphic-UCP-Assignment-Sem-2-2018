#include <stdio.h>
#include <stdlib.h>
#include "output.h"
#include "linked_list.h"
#include "log.h"

/*
Purpose: To print the invalid commands to terminal so that the user will know
         of any invalid commands that would cause the graphic to look not perfect
How it works: While the invalidCommandList is not empty, remove the first invalid
              invalid command line from list and print the invalid command
              line to stderr stream
*/
void printInvalidCommandList(LinkedList* invalidCommandList)
{
    char* invalidCommand = NULL;
    if(invalidCommandList-> head != NULL)
    {
        fprintf(stderr, "List of invalid commands:\n");
        while(invalidCommandList-> head != NULL)
        {
            invalidCommand = (char*)(removeFirst(invalidCommandList));
            fprintf(stderr, "%s\n", invalidCommand);
            free(invalidCommand);
        }
        fprintf(stderr, "\n");
    }
}

/*
Purpose: To print the logs of every move and draw command from a linked list of logs 
         that is executed by the program so that the user will know if the program
         is running correctly in terms of coordinates
How it works: graphics.log is opened in append mode. While the logList is not empty,
              remove the first node and print the string representation of the log
              to graphics.log
*/
void printLogList(LinkedList* logList)
{
    Log* log;
    FILE* file;
    file = fopen("graphics.log", "a");
    if(file == NULL)
    {
        perror("Error opening file");
    }
    else
    {
        if(ferror(file))
        {
            perror("Error reading from file\n");
        }
        else
        {
            if(logList->head != NULL)
            {
                fprintf(file, "---\n");
            }
            while(logList->head != NULL)
            {
                log = (Log*)(removeFirst(logList));
                fprintf(file, "    %s ( %7.3f,%7.3f),(%7.3f,%7.3f)\n", log->command, log->x1, log->y1, log->x2, log->y2);
                free(log);
            }
        }
        fclose(file);
    }
}