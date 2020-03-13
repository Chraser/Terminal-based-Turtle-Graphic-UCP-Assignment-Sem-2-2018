#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "TurtleGraphics.h"

int main(int argc, char** argv)
{
    FILE* file;
    LinkedList* commandList;
    char string[MAX_SIZE];
    char* mallocString;
    if(argc != 2)
    {
        printf("Run program with ./TurtleGraphics fileName\n");
    }
    else
    {
        file = fopen(argv[1], "r");
        /* check if the file is opened or not */
        if(file == NULL)
        {
            perror("Error opening file");
        }
        else
        {
            /* check if there is an error reading from the the file*/
            if(ferror(file))
            {
                perror("Error reading from file\n");
            }
            else
            {
                /* loading the contents of the file into a linked list*/
                commandList =  createLinkedList();
                while(fgets(string, sizeof(string), file) != NULL)
                {
                    mallocString = (char*)malloc(MAX_SIZE * sizeof(char));
                    strncpy(mallocString, string, MAX_SIZE);
                    insertLast(commandList, mallocString);
                }
                mallocString = NULL;
                if(commandList->head == NULL)
                {
                    perror("Error: File is empty");
                }
                else
                {
                    executeCommands(commandList);
                }
                free(commandList);
            }
            fclose(file);
        }
    }
    return 0;
}