# Compiles and Runs the program
OBJS = main.cpp

CC = g++

COMPILER_FLAGS = -Ofast

LINKER_FLAGS = -lSDL2

# Remember to change the entry in .git_ignore when editing the OBJ_NAME Macro
OBJ_NAME = program

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) && ./program

