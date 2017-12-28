To-Do List

This contains the necessary code to run a To-Do List program. It is an interactive console program that allows users to organize the tasks on their to-do list in one easy to use application. Featured functionality includes: adding, removing, and completing tasks, undoing and redoing actions, and saving tasks to a file or loading tasks from a file.

TASKS

Included in Tasks.h and Tasks.cpp are the blueprints and implementation for 4 types of task objects: generic, shopping, event, and homework. All of these tasks have a description and deadline but tasks other than type generic also have specialized information.  In the app, these task objects are never dealt with directly but they serve as storage for task info and provide details about themselves.

TASKLIST

TaskList.h and TaskList.cpp contain a defined and implemented data structure called TaskList. It uses a SortedVector(needed files are included, SortedVector.h and SortedVector.cpp) full of task pointers as its underlying data structure which is responsible for keeping tasks in order based on deadline. Relevant functionality includes adding tasks, removing tasks, getting a task from the list, and printing all stored tasks in short or detailed fashion.

TODOLISTDRIVER

This class is created by ToDoListDriver.h and ToDoListDriver.cpp and oversees the interaction between 2 TaskList objects: Outstanding and Completed. These 2 TaskLists keep track of their respective tasks. The driver offers functionality such as adding a new Outstanding task, completing a task, printing completed/outstanding tasks, saving and loading tasks given a file, and keeping track of used/undone commands in 2 stacks. Undone can be called so long as there are actions to be undone, but redo can only redo undone actions until an add/remove/complete command is used. 

TODOLISTAPP

This class is the "outer shell" of the program and contains an instance of ToDoListDriver, a helper function, and a function called run which actually executes the program. Inside of run lies the user interface which accepts the following commands: 
ADD – Adds a new task to your To-Do list 
PRINT – Displays your outstanding tasks succinctly 
DETAILED – Displays your outstanding tasks with specialized task details 
REMOVE – Removes an outstanding task 
COMPLETE – Marks an outstanding task as complete 
COMPLETED – Displays your completed tasks 
UNDO – Undoes the last ADD, DELETE, or COMPLETE command 
REDO – Redoes the last undone command  
SAVE – Saves your outstanding tasks to a file LOAD – Loads a file of outstanding tasks 
EXIT – Exits the application immediately 
HELP - Displays the above menu

The main function contains a ToDoListApp instance and calls its run function.

Compiling and running this program: Use the included makefile by entering "make". This will generate an executable named "ToDoList". Run the program by entering ./ToDoList