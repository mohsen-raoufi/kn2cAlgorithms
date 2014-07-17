#include "playgameondefensive.h"

PlayGameOnDefensive::PlayGameOnDefensive(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOnDefensive", worldmodel, parent)
{
}

int PlayGameOnDefensive::enterCondition()
{
    if(wm->cmgs.gameOn() && wm->kn->ActiveAgents().size() < 4)
        return 100;
    else
        return 0;

    return 0;
}

void PlayGameOnDefensive::execute()
{
}
