#ifndef TODOLISTAPP_H
#define TODOLISTAPP_H

#include "ToDoListDriver.h"

class ToDoListApp
{
    //single function which deals with input/output
    //which executes until program ends
    public:
        void run();

    //single instance of ToDoListDriver to carry out functionality
    //helper function to print available class functionality
    private:
        ToDoListDriver core;
        void printHelp();
};

#endif // TODOLISTAPP_H
