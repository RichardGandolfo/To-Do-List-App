#ifndef TODOLISTDRIVER_H
#define TODOLISTDRIVER_H

#include "TaskList.h"
#include <fstream>
#include <stack>

struct Command
{
    string type;
    GenericTask * tracker;
};

class ToDoListDriver
{
    //oversees manipulation of the 2 tasklist objects
    //creates, removes, and prints info about both lists
    //can save outstanding tasks to file or load from file
    //can undo and redo commands used by user
    //checks if list is empty for both outstanding and completed
    public:
        void createNewOutstanding(char input);
        void removeOutstanding(unsigned int position);
        void completeOutstanding(unsigned int position);
        void printOutstanding();
        void printCompleted();
        void printOutstandingDetailed();
        void saveOutstanding(string filename);
        void loadOutstanding(string filename);
        void undo();
        void redo();
        bool emptyCheck();
        bool emptyCheckComp();

    private:
        //two instances of TaskList objects - one for outstanding and one for completed
        //instance of command object which helps track used commands
        //two stacks containing command objects, one for aiding in undo and other for redo
        //bool var helps tell if redo can be executed
        //basicinfo is a helper function which fills in common info between all 4 task classes
        TaskList Outstanding;
        TaskList Completed;
        Command cmd;
        stack<Command> usedCommands;
        stack<Command> undoneCommands;
        bool redoStatus=false;
        void clearRedo();
        void BasicInfo(GenericTask*);
};

#endif // TODOLISTDRIVER_H
