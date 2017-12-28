#ifndef TASKLIST_H
#define TASKLIST_H

#include "SortedVector.h"

class TaskList
{
    public:
        //destructor deletes all pointers and sets to null in sortedvector
        //class functionality adds a generictask pointer to the sortedvector,
        //prints info about the objects that the pointers point to, removes
        //a task and helper functions and size/clear/return specific pointer
        ~TaskList();
        void addTask(GenericTask*temp) {list.insert(temp);}
        void printList();
        void printListDetailed();
        void removeTask(unsigned int position);
        GenericTask* getTask(unsigned int position);
        int size() {return list.size();}
        bool empty() {return list.empty();}
        void clear() {list.clear();}
        int locate(GenericTask * descr);

    private:
        // sortedvector object containing base class pointers
        SortedVector<GenericTask*, Comparator> list;
};

#endif
