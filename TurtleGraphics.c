#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "log.h"
#include "TurtleGraphics.h"
#include "effects.h"
#include "linked_list.h"
#include "utility.h"
#include "output.h"

/*
Purpose: To execute the commands from the commandList if valid and if not valid
         added to the invalid command list for printing to stderr purposes.
How it works: Checks if the first string in the command is a valid command
              then check if the parameter supplied is valid then execute if valid
              else add commandLine to invalidCommandList. Finally it calls
              the printInvalidCommandList and printLogList and free all memory
              allocated to the heap that has not been freed
*/
void executeCommands(LinkedList* commandList)
{
    LinkedList* invalidCommandList;
    LinkedList* logList;
    TurtleGraphics* turtleGraphics;
    char* commandLine;
    char command[MAX_COMMAND_SIZE];
    char excessInCommandLine[5];
    double realNum;
    char pattern;
    int intNum;
    
    turtleGraphics = (TurtleGraphics*)malloc(sizeof(TurtleGraphics));
    turtleGraphics->x = 0.0;
    turtleGraphics->y = 0.0;
    turtleGraphics->angle = 0.0;
    #ifndef SIMPLE
    turtleGraphics->fg = 7;
    turtleGraphics->bg = 0;
    #else
    turtleGraphics->fg = 0;
    turtleGraphics->bg = 15;
    #endif
    turtleGraphics->pattern = '+';
    
    setFgColour(turtleGraphics->fg);
    setBgColour(turtleGraphics->bg);
    
    invalidCommandList = createLinkedList();
    logList = createLinkedList();
    
    clearScreen();
    
    while(commandList->head != NULL)
    {
        commandLine = (char*)removeFirst(commandList);
        sscanf(commandLine, "%s", command);
        changeToUpperCase(command);
        if(strcmp(command, "MOVE") == 0)
        {
            if(sscanf(commandLine, "%*s %lf %s", &realNum, excessInCommandLine) == 1)
            {
                moveTurtleGraphic(turtleGraphics, realNum, logList);
                free(commandLine);
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else if(strcmp(command, "DRAW") == 0)
        {
            if(sscanf(commandLine, "%*s %lf %s", &realNum, excessInCommandLine) == 1)
            {
                drawTurtleGraphic(turtleGraphics, realNum, logList);
                free(commandLine);
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else if(strcmp(command, "ROTATE") == 0)
        {
            if(sscanf(commandLine, "%*s %lf %s", &realNum, excessInCommandLine) == 1)
            {
                updateAngle(turtleGraphics, realNum);
                free(commandLine);
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else if(strcmp(command, "FG") == 0)
        {
            if(sscanf(commandLine, "%*s %d %s", &intNum, excessInCommandLine) == 1)
            {
                if(validateColour(intNum, MIN_FG, MAX_FG) == 1)
                {
                    #ifndef SIMPLE
                    turtleGraphics->fg = intNum;
                    setFgColour(turtleGraphics->fg);
                    #endif
                    free(commandLine);
                }
                else
                {
                    insertLast(invalidCommandList, commandLine);
                }
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else if(strcmp(command, "BG") == 0)
        {
            if(sscanf(commandLine, "%*s %d %s", &intNum, excessInCommandLine) == 1)
            {
                if(validateColour(intNum, MIN_BG, MAX_BG) == 1)
                {
                    #ifndef SIMPLE
                    turtleGraphics->bg = intNum;
                    setBgColour(turtleGraphics->bg);
                    #endif
                    free(commandLine);
                }
                else
                {
                    insertLast(invalidCommandList, commandLine);
                }
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else if(strcmp(command, "PATTERN") == 0)
        {
            if(sscanf(commandLine, "%*s %c %s", &pattern, excessInCommandLine) == 1)
            {
                turtleGraphics->pattern = pattern;
                free(commandLine);
            }
            else
            {
                insertLast(invalidCommandList, commandLine);
            }
        }
        else
        {
            insertLast(invalidCommandList, commandLine);
        }
    }
    penDown();
    printInvalidCommandList(invalidCommandList);
    printLogList(logList);
    free(invalidCommandList);
    free(logList);
    free(turtleGraphics);
}

/*
Purpose: To execute the MOVE command and update the logList and turtleGraphics
How it works: A log is created with the MOVE command and the initial position
              of turtleGraphics and the updated position of turtleGraphics.
              turtleGraphics' x and y coordinates are updated with 
              change in x and y using angle, distance, and angleInRadians(), and sin() 
              and cos() functions  from math.h  
*/
void moveTurtleGraphic(TurtleGraphics* turtleGraphics, double distance, LinkedList* logList)
{
    Log* log;
    log = (Log*)malloc(sizeof(Log));
    log->command = "MOVE";
    log->x1 = turtleGraphics->x;
    log->y1 = turtleGraphics->y;
    
    if(distance != 0)
    {
        turtleGraphics->x += cos(angleInRadians(turtleGraphics->angle)) * (distance);
        turtleGraphics->y -= sin(angleInRadians(turtleGraphics->angle)) * (distance);
    }
    
    log->x2 = turtleGraphics->x;
    log->y2 = turtleGraphics->y;
    #ifdef DEBUG
    fprintf(stderr, "%s ( %7.3f,%7.3f),(%7.3f,%7.3f)\n", log->command, log->x1, log->y1, log->x2, log->y2);
    #endif
    insertLast(logList, log);
}

/*
Purpose: To execute the DRAW command and update the logList and turtleGraphics
How it works: A log is created with the DRAW command and the initial position
              of turtleGraphics and the updated position of turtleGraphics.
              turtleGraphics' x and y coordinates are updated with 
              change in x and y using angle, distance - 1, and angleInRadians(), and sin() 
              and cos() functions  from math.h. 
              Then line() is called with x1, y1, x2, y2, pointer to plotPoint function
              and the pointer to the pattern
*/
void drawTurtleGraphic(TurtleGraphics* turtleGraphics, double distance, LinkedList* logList)
{
    Log* log;
    int x1, y1, x2, y2;
    log = (Log*)malloc(sizeof(Log));
    log->command = "DRAW";
    log->x1 = turtleGraphics->x;
    log->y1 = turtleGraphics->y;
    
    if(distance != 0)
    {
        x1 = round(turtleGraphics->x);
        y1 = round(turtleGraphics->y);
        
        turtleGraphics->x += cos(angleInRadians(turtleGraphics->angle)) * (distance - 1);
        turtleGraphics->y -= sin(angleInRadians(turtleGraphics->angle)) * (distance - 1);
        
        x2 = round(turtleGraphics->x);
        y2 = round(turtleGraphics->y);
        
        line(x1, y1, x2, y2, &plotPoint, &(turtleGraphics->pattern));
        
        turtleGraphics->x += cos(angleInRadians(turtleGraphics->angle));
        turtleGraphics->y -= sin(angleInRadians(turtleGraphics->angle));
    }
    
    log->x2 = turtleGraphics->x;
    log->y2 = turtleGraphics->y;
    #ifdef DEBUG
    fprintf(stderr, "%s ( %7.3f,%7.3f),(%7.3f,%7.3f)\n", log->command, log->x1, log->y1, log->x2, log->y2);
    #endif
    insertLast(logList, log);
}

/*
Purpose: To convert the angle in degrees to angle in radians
         so that the sin() and cos() from math.h can be used since
         they work in radians
How it works: Radians is calculated by the result from angle multiplying by PI constant
              and divided by 180
*/
double angleInRadians(double angle)
{
    double radians;
    radians = angle *  PI / 180;
    return radians;
}

/*
Purpose: To update the angle in turtleGraphics and adjust the angle 
         to be in the range of 0 to 359 inclusive
How it works: Angle in turtleGraphics is updated with changeinAngle 
              and 360 is added or substracted if angle in turtleGraphics
              is no longer in the range of 0 to 359 inclusive
*/
void updateAngle(TurtleGraphics* turtleGraphics, double changeInAngle)
{
    turtleGraphics->angle += changeInAngle;
    while(turtleGraphics->angle < MIN_ANGLE)
    {
        turtleGraphics->angle += 360;
    }
    while(turtleGraphics->angle > MAX_ANGLE)
    {
        turtleGraphics->angle -= 360;
    }
}

/*
Purpose: To validate that the colour code supplied is in the
         range specified
How it works: 1 is returned if the number is in range of min and max 
              else 0 is returned
*/
int validateColour(int number, int min, int max)
{
    int isValid;
    if((number >= min) && (number <= max))
    {
        isValid = 1;
    }
    else
    {
        isValid = 0;
    }
    return isValid;
}

/*
Purpose: To plot a character at current location 
How it works: The data is typecasted to a char* then to a char and printed
              to stdout
*/
void plotPoint(void* data)
{
    printf("%c", *((char*)data));
}
