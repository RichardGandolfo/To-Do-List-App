#include "Tasks.h"

//Shopping class function which prints all the items contained
//in the class' private string vector.
void Shopping::printList()
{
    for (int i=0; i<listOfItems.size(); i++)
    {
        cout <<"    "<< listOfItems.at(i) <<endl;
    }
}

//Leverages the generic printInfo function and
//the printList function to yield a detailed print
void Shopping::printDetailed()
{
    printInfo();
    cout << "    ITEMS TO PURCHASE: " << endl;
    printList();
}

//Prints generic info and specialized event info
void Event::printDetailed()
{
    printInfo();
    cout << "    WHERE: " << getLocation() << endl;
    cout << "    WHEN: " << getTime() << endl;
}

//Prints generic info and specialized homework info
void Homework::printDetailed()
{
    printInfo();
    cout << "    SUBJECT: " << getSubject() << endl;
}

//Returns a formatted string of all the strings in the private
//string vector, delimited by a | character and when an index
//Assists with outputting to a file.
string Shopping::formatItems()
{
    string items="";
    for (int i=0; i<listOfItems.size(); i++)
    {
        if (i!=listOfItems.size()-1)
        {
            items+=listOfItems.at(i)+"|";
        }
        else
        {
            items+=listOfItems.at(i);
        }
    }
    return items;
}

//Converts an int to a string so it can be concatenated to
//the formatted string, aids in outputting to file
string GenericTask::to_string(int number)
{
    string result;
    ostringstream convert;
    convert << number;
    result=convert.str();
    return result;
}
