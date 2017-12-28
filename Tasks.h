#ifndef TASKS_H
#define TASKS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class GenericTask
{
    //base class, all tasks have strings: deadline and description. prints its own class info
    //can return strings and ints that describe itself including a formatting function
    //which aids in saving info to a file, They are overridden by derived classes as are print functions
    //all other task classes inherit from this class
    public:
        void setDescription(string descr) {description=descr;}
        void setDeadline(int due) {deadline=due;}
        string getDescription() {return description;}
        int getDeadline() {return deadline;}
        virtual void printInfo()
        {
            cout << "(" << deadline << " day(s) from now) " << description <<endl;
        }
        virtual void printDetailed() {printInfo();}
        virtual string getType() {return "G";}
        virtual string formatInfo()
        {
            return "G|"+to_string(deadline)+"|"+description;
        }

        string to_string(int);

    protected:
        string description;
        int deadline;
};

class Shopping: public GenericTask
{
    //contains a vector to store a list of string shopping items
    //overwritten functionality to more appropriately describe class
    public:
        void addItemToList(string item) {listOfItems.push_back(item);}
        void printList();
        virtual void printInfo()
        {
            cout << "(" << deadline << " day(s) from now) " << "[Shopping] " << description <<endl;
        }
        virtual void printDetailed();
        virtual string getType() {return "S";}
        string formatItems();
        virtual string formatInfo()
        {
            return "S|"+to_string(deadline)+"|"+description+"|"+formatItems();
        }

    private:
        vector<string> listOfItems;
};

class Event: public GenericTask
{
    // additional private members include strings to represent location/time
    // has necessary setter functions to update specific members
    public:
        void setLocation(string loc) {location=loc;}
        void setTime(string timeVal) {time=timeVal;}
        string getLocation() {return location;}
        string getTime() {return time;}
        virtual void printInfo()
        {
            cout << "(" << deadline << " day(s) from now) " << "[Event] " << description <<endl;
        }
        virtual void printDetailed();
        virtual string getType() {return "E";}
        virtual string formatInfo()
        {
            return "E|"+to_string(deadline)+"|"+description+"|"+location+"|"+time;
        }

    private:
        string location;
        string time;
};

class Homework: public GenericTask
{
    // only unique data member is a string representing a subject
    public:
        void setSubject(string subj) {subject=subj;}
        string getSubject() {return subject;}
        virtual void printInfo()
        {
            cout << "(" << deadline << " day(s) from now) " << "[Homework] " << description <<endl;
        }
        virtual void printDetailed();
        virtual string getType() {return "H";}
        virtual string formatInfo()
        {
            return "H|"+to_string(deadline)+"|"+description+"|"+subject;
        }

    private:
        string subject;
};

#endif // TASKS_H
