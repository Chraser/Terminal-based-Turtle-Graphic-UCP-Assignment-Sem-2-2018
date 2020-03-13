/*Forward declarations only. Comments for each individual function is at the definition of function*/
#ifndef TURTLEGRAPHICS_H
#define TURTLEGRAPHICS_H
#include "linked_list.h"
/*
TYPEDEF Struct TurtleGraphics
Purpose: To store the current x,y coordinate, angle, foreground, background and
         pattern of the TurtleGraphics program
*/
typedef struct TurtleGraphics{
    double x;
    double y;
    double angle;
    int fg;
    int bg;
    char pattern;
} TurtleGraphics;
#define MAX_SIZE 21
#define MAX_COMMAND_SIZE 8
#define MIN_FG 0
#define MAX_FG 15
#define MIN_BG 0
#define MAX_BG 7
#define PI 3.14159265358979323846
#define MIN_ANGLE 0
#define MAX_ANGLE 360
void executeCommands(LinkedList* commandList);
void moveTurtleGraphic(TurtleGraphics* turtleGraphics, double distance, LinkedList* logList);
void drawTurtleGraphic(TurtleGraphics* turtleGraphics, double distance, LinkedList* logList);
double angleInRadians(double angle);
void updateAngle(TurtleGraphics* turtleGraphics, double changeInAngle);
int validateColour(int number, int min, int max);
void plotPoint(void* data);
#endif