#include "ActionAdd.h"

ActionAdd::ActionAdd(Repository& repository, Song addedSong) :
    repository(repository),
    addedSong(addedSong)
{
}

void ActionAdd::executeUndo()
{
    this->repository.removeSong(this->addedSong);
}

void ActionAdd::executeRedo()
{
    this->repository.addSong(this->addedSong);
}
