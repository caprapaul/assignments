#pragma once

#include "Action.h"
#include "Repository.h"
#include "Song.h"

class ActionRemove :
    public Action
{
private:
    Repository& repository;
    Song removedSong;

public:
    ActionRemove(Repository& repository, Song removedSong);

    virtual void executeUndo() override;
    virtual void executeRedo() override;
};

