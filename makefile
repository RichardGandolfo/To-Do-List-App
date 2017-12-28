CC = g++
LFLAGS = -std=c++11
CFLAGS = -c -Wall


SOURCES = main.cpp SortedVector.cpp Tasks.cpp TaskList.cpp ToDoListDriver.cpp ToDoListApp.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE_NAME = ToDoList

all: $(EXECUTABLE_NAME)

$(EXECUTABLE_NAME): $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $(LFLAGS) $< -o $@

clean:
	$(RM) *.o *~ $(EXECUTABLE_NAME)
