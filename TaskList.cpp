#include "TaskList.h"

//Destructor deletes allocated memory in each index of the structure
//and sets all pointers to null. Then The list is cleared.
TaskList::~TaskList()
{
    for (int i=0; i<list.size(); i++)
    {
        delete list.at(i);
        list.at(i)=NULL;
    }

    list.clear();
}

//Uses get function to call each pointer and uses that
//pointer to call its print function, goes through all indexes
void TaskList::printList()
{
    for (int i=0; i<list.size(); i++)
    {
        cout << i+1 << ". ";
        getTask(i)->printInfo();
    }
    cout << endl;
}

//Identical functionality to previous print function,
//calls the printDetailed function instead
void TaskList::printListDetailed()
{
    for (int i=0; i<list.size(); i++)
    {
        cout << i+1 << ". ";
        getTask(i)->printDetailed();
    }
    cout << endl;
}

//pointer is set to null and taken out of list
void TaskList::removeTask(unsigned int position)
{
    list.at(position)=NULL;
    list.remove(position);
}

//Gets pointer at desired position of the vector
GenericTask* TaskList::getTask(unsigned int position)
{
    return list.at(position);
}

//given a pointer, this function returns an int telling
//which index of vector contains that pointer
int TaskList::locate(GenericTask * temp)
{
    for (int i=0; i<list.size(); i++)
    {
        if (getTask(i)==temp)
        {
            return i;
        }
    }
}
