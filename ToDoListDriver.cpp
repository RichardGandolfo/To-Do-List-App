#include "ToDoListDriver.h"

//Empty check and calls print function of Outstanding
void ToDoListDriver::printOutstanding()
{
    if (emptyCheck()) {return;}
    Outstanding.printList();
}

//Prints Completed's contents by calling its print function
void ToDoListDriver::printCompleted()
{
    if (Completed.empty())
    {
        cout << "You have no completed tasks!" << endl;
        cout << endl;
    }

    Completed.printList();
}

//Calls Outstanding's detailed print function
void ToDoListDriver::printOutstandingDetailed()
{
    if (emptyCheck()) {return;}
    Outstanding.printListDetailed();
}

//Depending on user input letter, the task associated with that
//char is created dynamically and then filled out in accordance with its class
//specialty. The undo stack is also filled with commands to track used commands.
//The newly created task is then added to the Outstanding TaskList.
void ToDoListDriver::createNewOutstanding(char input)
 {
    //creates a base class task
    if (input == 'G' or input == 'g')
    {
        //pointer creates new task object
        GenericTask * gt;
        gt = new GenericTask;
        //All 4 class type pointers are passed into this helper function to
        //get and set the common/shared class info
        BasicInfo(gt);
        //Command object is updated with type of command
        //and pointer points to new object
        cmd.type="add";
        cmd.tracker=gt;
        usedCommands.push(cmd);
        //Task pointer is added to Outstanding
        Outstanding.addTask(gt);
    }

    //Creates a shopping task
    else if (input == 'S' or input =='s')
    {
        Shopping * sh;
        string item;
        sh = new Shopping;
        BasicInfo(sh);

        //Lets user add items to the vector of the Shopping object
        cout <<"What items do you need to buy? [Type your item and press ENTER to add another item. Type DONE to complete the list.]" << endl;
        while (getline(cin, item))
        {
            if (item=="DONE") {break;}
            sh->addItemToList(item);
        }
        //Command object helps track command used, add
        cmd.type="add";
        cmd.tracker=sh;
        usedCommands.push(cmd);

        Outstanding.addTask(sh);
    }

    //Creates a new event task
    else if (input == 'E' or input == 'e')
    {
        Event * ev;
        string where, when;
        ev = new Event;
        BasicInfo(ev);

        //Gets and sets specialized event info using pointer
        cout << "Where is this event taking place?" << endl;
        getline(cin, where);
        ev -> setLocation(where);

        cout << "When is this event taking place?" << endl;
        getline(cin, when);
        ev -> setTime(when);

        //Command object notes string and pointer
        //points to specialized pointer
        cmd.type="add";
        cmd.tracker=ev;
        usedCommands.push(cmd);

        Outstanding.addTask(ev);
    }

    //Creates a homework task
    else if (input == 'H' or input == 'h')
    {
        Homework * hw;
        string subject;
        hw = new Homework;
        BasicInfo(hw);

        //Gets string for subject and uses Homework pointer to
        //call set function to fill in data
        cout << "What subject is this homework task for?" << endl;
        getline (cin, subject);
        hw -> setSubject(subject);

        //Command object notes type of command used,
        //pointer points to homework pointer
        cmd.type="add";
        cmd.tracker=hw;
        usedCommands.push(cmd);

        Outstanding.addTask(hw);
    }

    //Returns if input does not match any defined command
    else
    {
        cout << "Invalid command" << endl << endl;
        return;
    }

    cout << "Task added successfully" << endl;
    cout << endl;
    // If this function is used, redo is invalid to use
    redoStatus=false;
    clearRedo();
}

//Helper function, all 4 types of pointers are passed into this
//function since they share common data: description and days
void ToDoListDriver::BasicInfo(GenericTask*temp)
{
    int days;
    string description;

    cout << "In how many days is this task due? " << endl;
    cin >> days;
    //Temporary pointer sets days using the input int
    temp -> setDeadline(days);

    cout << "How would you describe this task? " << endl;
    cin.get();
    getline(cin, description);
    //Temporary pointer uses task set function to update description
    temp -> setDescription(description);
}

//Helper function, if Outstanding list is empty then notify user with message
bool ToDoListDriver::emptyCheck()
{
    if (Outstanding.empty())
    {
        cout << "You have no outstanding tasks!" << endl<<endl;
        return true;
    }
    else
    {
        return false;
    }
}

//Helper function, same as  previous function but for the Completed list
bool ToDoListDriver::emptyCheckComp()
{
    if (Completed.empty())
    {
        cout << "You have no completed tasks!" <<endl<<endl;
        return true;
    }
    else {return false;}
}

//Given a number on the list, remove the task in that place on the list
void ToDoListDriver::removeOutstanding(unsigned int position)
{
    if (emptyCheck() or position-1 >= Outstanding.size()) {return;}
    //Command tracking, type noted and pointer points to object about to be removed
    cmd.type="remove";
    cmd.tracker=Outstanding.getTask(position-1);
    usedCommands.push(cmd);
    //Removed in position 1 less than user to input to account for
    //0 based index, first item on list is in position 0.
    Outstanding.removeTask(position-1);
    //Immediate following this action, redo is invalid
    redoStatus=false;
    clearRedo();
    cout << "Task removed successfully!" << endl<<endl;
}

void ToDoListDriver::completeOutstanding(unsigned int position)
{
    if (emptyCheck() or position-1 >= Outstanding.size()) {return;}
    //Command object tracks completed object
    cmd.type="complete";
    cmd.tracker=Outstanding.getTask(position-1);
    usedCommands.push(cmd);
    //Chosen object's pointer added to Completed's list
    Completed.addTask(Outstanding.getTask(position-1));
    //Chosen pointer is also removed from Outstanding's list
    Outstanding.removeTask(position-1);
    //Immediately after this command, redo is invalid
    redoStatus=false;
    clearRedo();
    cout << "Tasks completed successfully!" << endl<<endl;
}

void ToDoListDriver::saveOutstanding(string filename)
{
    if (emptyCheck()) {return;}
    ofstream saver;
    //Ostream opens desired file
    saver.open(filename);
    //Using each task class' format function, all pointers call their respective
    //format function to get a string which will be outputted to the file.
    for (int i=0; i<Outstanding.size(); i++)
    {
        saver << Outstanding.getTask(i)->formatInfo()<<endl;
        saver << endl;
    }
    saver.close();

    cout << "Tasks saved successfully!" << endl<<endl;
}

//Loads tasks from a properly formatted file into the Outstanding list
void ToDoListDriver::loadOutstanding(string filename)
{
    string line;
    ifstream loader;
    loader.open(filename);
    //Takes each line in file and makes it into a single string
    while (getline(loader, line))
    {
        //Depending on what the identifying char in position 0 is,
        //the necessary if block is executed
        if (line[0]=='G')
        {
            int i=2;
            int deadline;
            GenericTask * gt;
            string strdeadline;
            string description="";

            //Breaks up portion of string until a | char is hit
            //and then is saved as the deadline
            for (i; ;i++)
            {
                if (line[i]=='|') {break;}
                strdeadline+=line[i];
            }
            //string deadline is converted to an int
            istringstream (strdeadline) >> deadline;

            //string is broken up from the end of the int
            //until the end of the string, this becomes description
            for (i; i<line.size(); i++)
            {
                if (line[i]!='|')
                {
                    description+=line[i];
                }
            }

            //New task is created and then set with info and finally added
            //to the Outstanding list
            gt = new GenericTask;
            gt->setDeadline(deadline);
            gt->setDescription(description);

            Outstanding.addTask(gt);
        }

        if (line[0]=='E')
        {
            int i=2;
            int deadline;
            Event * ev;
            string strdeadline;
            string description="";
            string where="",when="";

            //Loop gets deadline as a string and then it's
            //converted to an int
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                strdeadline+=line[i];
            }
            istringstream (strdeadline) >> deadline;

            //Loop picks up from where previous left off and
            //continues until next | char to get description.
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                description+=line[i];
            }

            //Using same logic, loop gets location member
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                where+=line[i];
            }

            //Using same logic loop gets time member
            for (i; i<line.length(); i++)
            {
                when+=line[i];
            }

            //Event pointer fills out info
            ev = new Event;
            ev->setDeadline(deadline);
            ev->setDescription(description);
            ev->setLocation(where);
            ev->setTime(when);

            //Event pointer added to Outstanding list
            Outstanding.addTask(ev);
        }

        if (line[0]=='S')
        {
            int i=2;
            int deadline;
            Shopping * sh;
            string strdeadline,item="",description="";

            //Loops breaks up string to get deadline then converts to int
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                strdeadline+=line[i];
            }
            istringstream (strdeadline) >> deadline;

            //Loop breaks up string to get portion representing description
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                description+=line[i];
            }

            sh = new Shopping;
            //Loops breaks up string to get each individual item and then
            //adds it to private vector of Shopping class using set functionality
            for (i; i<line.length(); i++)
            {
                if (line[i]!='|')
                {
                    item+=line[i];
                }
                if (line[i]=='|' or i==line.length()-1)
                {
                    sh ->addItemToList(item);
                    item="";
                }
            }
            sh->setDeadline(deadline);
            sh->setDescription(description);
            //After info is set, shopping pointer is added to Outstanding list
            Outstanding.addTask(sh);
        }

        if (line[0]=='H')
        {
            int i=2;
            int deadline;
            Homework * hw;
            string strdeadline;
            string subject="",description="";

            //Loops gets deadline portion as string and converts to an int
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                strdeadline+=line[i];
            }
            istringstream (strdeadline) >> deadline;

            //Loops gets portion representing description
            for (i; ;i++)
            {
                if (line[i]=='|')
                {
                    i++;
                    break;
                }
                description+=line[i];
            }

            //Loop gets final portion representing string subject
            for (i; i<line.length(); i++)
            {
                subject+=line[i];
            }
            hw = new Homework;
            hw ->setDeadline(deadline);
            hw ->setDescription(description);
            hw ->setSubject(subject);
            //After info is set, HW pointer added to Outstanding list
            Outstanding.addTask(hw);
        }
    }

    loader.close();
    cout << "Tasks loaded successfully!"<<endl<<endl;
}

//Using the stack of relevant used commands, the type of command represented as a string
//is checked and the "inverse" command is used on the object the pointer is tracking
void ToDoListDriver::undo()
{
    if (usedCommands.empty()) {cout<<"You have no commands to undo!"<<endl<<endl;}
    else if (usedCommands.top().type=="add")
    {
        //Executes opposite of add which is remove
        Outstanding.removeTask(Outstanding.locate(usedCommands.top().tracker));
        //This stack tracks the commands which were undone
        undoneCommands.push(usedCommands.top());
        usedCommands.pop();
        cout << "ADD command undone successfully"<< endl << endl;
    }
    else if (usedCommands.top().type=="remove")
    {
        //Executes opposite of remove which is add
        Outstanding.addTask(usedCommands.top().tracker);
        undoneCommands.push(usedCommands.top());
        usedCommands.pop();
        cout << "REMOVE command undone successfully"<< endl << endl;
    }
    else if (usedCommands.top().type=="complete")
    {
        //Executes opposite of complete which is broken into 2 steps
        //First the pointer is removed from Completed
        //Then the pointer is added to Outstanding
        Outstanding.addTask(usedCommands.top().tracker);
        Completed.removeTask(Completed.locate(usedCommands.top().tracker));
        undoneCommands.push(usedCommands.top());
        usedCommands.pop();
        cout << "COMPLETE command undone successfully"<< endl << endl;
    }
    redoStatus=true;
}

//Allows user to redo an undone task as long as previous command was not add/remove/complete
void ToDoListDriver::redo()
{
    if (!redoStatus or undoneCommands.empty())
    {
        cout << "You have no commands to redo!" <<endl<<endl;
        return;
    }
    //Since this redoes a task, the function executes the same command rather than opposite
    if (undoneCommands.top().type=="add")
    {
        Outstanding.addTask(undoneCommands.top().tracker);
        usedCommands.push(undoneCommands.top());
        undoneCommands.pop();
        cout << "ADD command redone successfully."<<endl<<endl;
    }
    else if (undoneCommands.top().type=="remove")
    {
        Outstanding.removeTask(Outstanding.locate(undoneCommands.top().tracker));
        usedCommands.push(undoneCommands.top());
        undoneCommands.pop();
        cout << "REMOVE command redone successfully."<<endl<<endl;
    }
    else if (undoneCommands.top().type=="complete")
    {
        Completed.addTask(undoneCommands.top().tracker);
        Outstanding.removeTask(Outstanding.locate(undoneCommands.top().tracker));
        usedCommands.push(undoneCommands.top());
        undoneCommands.pop();
        cout << "COMPLETE command redone successfully."<<endl<<endl;
    }
}

//Helper function which clears stack of undone tasks when redo is no longer valid
void ToDoListDriver::clearRedo()
{
    while (!undoneCommands.empty())
    {
        undoneCommands.pop();
    }
}
