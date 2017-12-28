#include "ToDoListApp.h"

//This function is nested completely inside of a while loop. The while loop evaluates to
//true so long as the user does not enter 'exit'. A string is constantly being
//read in and depending on its value, the appropriate if block executes and calls
//the necessary function of the ToDoListDriver core. This function is the main interaction
//with the user and couts statements depending on the string value read in by the cin at the
//end of the loop which ensures the function executes as long as it is needed.
void ToDoListApp::run()
{
    string input;
    cout << "Welcome to your To-Do List! For a full list of commands, type HELP." << endl << endl;

    while (input != "EXIT" and input != "exit")
    {
        if (input=="ADD" or input=="add")
        {
            cout << "What type of task is this? [G: Generic, S: Shopping, E: Event, H: Homework]" << endl;
            char type;
            cin >> type;
            core.createNewOutstanding(type);
        }

        if (input=="PRINT" or input=="print")
        {
            core.printOutstanding();
        }

        if (input=="DETAILED" or input=="detailed")
        {
            core.printOutstandingDetailed();
        }

        if (input=="REMOVE" or input=="remove")
        {
            if (core.emptyCheck()) {}
            else
            {
                cout << "Which task would you like to remove?" <<endl;
                int number;
                cin >> number;
                core.removeOutstanding(number);
            }
        }

        if (input=="COMPLETE" or input=="complete")
        {
            if (core.emptyCheck()) {}
            else
            {
                cout << "Which task would you like to complete?"<<endl;
                int number;
                cin >> number;
                core.completeOutstanding(number);
            }
        }

        if (input=="COMPLETED" or input=="completed")
        {
            if (core.emptyCheckComp()) {}
            else
            {
                core.printCompleted();
            }
        }

        if (input=="UNDO" or input=="undo")
        {
            core.undo();
        }

        if (input=="REDO" or input=="redo")
        {
            core.redo();
        }

        if (input=="SAVE" or input=="save")
        {
            if (core.emptyCheck()){}
            else
            {
                cout << "Where would you like to save your outstanding tasks?"<<endl;
                string file;
                cin >> file;
                core.saveOutstanding(file);
            }
        }

        if (input=="LOAD" or input=="load")
        {
            cout << "What file would you like to load outstanding tasks from?" <<endl;
            string file;
            cin >> file;
            core.loadOutstanding(file);
        }

        if (input=="HELP" or input=="help")
        {
            printHelp();
        }

        cin >> input;
    }

    cout << "Thank you for using ToDoList App!" << endl;
}

//Helper function, prints help menu when needed in run function
void ToDoListApp::printHelp()
{
    cout << "ADD - Adds a new task to your To-Do list" << endl;
    cout << "PRINT - Displays your outstanding tasks succinctly" << endl;
    cout << "DETAILED - Displays your outstanding tasks with specialized task details" << endl;
    cout << "REMOVE - Removes an outstanding task" << endl;
    cout << "COMPLETE - Marks an outstanding task as complete" << endl;
    cout << "COMPLETED - Displays your completed tasks" << endl;
    cout << "UNDO - Undoes the last ADD, REMOVE, or COMPLETE command" << endl;
    cout << "REDO - Redoes the last undone command" << endl;
    cout << "SAVE - Saves your outstanding tasks to a file" << endl;
    cout << "LOAD - Loads a file of outstanding tasks" << endl;
    cout << "EXIT - Exits the application immediately" << endl<<endl;
}
