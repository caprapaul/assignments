#include "command.h"
#include <stdlib.h>

int CommandCreate(Command** command, CommandFunction execute, CommandFunction undo)
{
    *command = (Command*)malloc(sizeof(Command));

    if (*command == NULL)
    {
        return -COMMAND_ERROR;
    }

    (*command)->execute = execute;
    (*command)->undo = undo;

    return COMMAND_SUCCESS;
}

int CommandDestroy(Command** command)
{
    free(*command);
    *command = NULL;

    return COMMAND_SUCCESS;
}
