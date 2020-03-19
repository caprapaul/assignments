#pragma once

typedef int(*CommandFunction)();

#define COMMAND_SUCCESS 0
#define COMMAND_ERROR -1

typedef struct 
{
    CommandFunction execute;
    CommandFunction undo;
} Command;

int CommandCreate(Command** command, CommandFunction execute, CommandFunction undo);
int CommandDestroy(Command** command);
