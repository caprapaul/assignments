#include "ActionRemove.h"

ActionRemove::ActionRemove(Repository & repository, Song removedSong):
    repository(repository),
    removedSong(removedSong)
{
}

void ActionRemove::executeUndo()
{
    this->repository.addSong(this->removedSong);
}

void ActionRemove::executeRedo()
{
    this->repository.removeSong(this->removedSong);
}
