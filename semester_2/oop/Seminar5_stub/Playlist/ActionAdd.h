#pragma once

#include "Action.h"
#include "Repository.h"
#include "Song.h"

class ActionAdd :
    public Action
{
private:
    Repository& repository;
    Song addedSong;

public:
    ActionAdd(Repository& repository, Song addedSong);

    virtual void executeUndo() override;
    virtual void executeRedo() override;
};

