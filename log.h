#ifndef LOG_H
#define LOG_H
/*
TYPEDEF Struct Log
Purpose: To store the command and 2 sets of x,y coordinates for a log
*/
typedef struct{
    char* command;
    double x1;
    double y1;
    double x2;
    double y2;
} Log;
#endif