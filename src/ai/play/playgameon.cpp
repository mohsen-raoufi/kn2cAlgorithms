#include "playgameon.h"

PlayGameOn::PlayGameOn(WorldModel *worldmodel, QObject *parent) :
    Play("PlayGameOn", worldmodel, parent)
{
}

int PlayGameOn::enterCondition()
{
    if(wm->cmgs.gameOn() && wm->kn->ActiveAgents().size() > 3)
        return 100;
    else
        return 0;

    return 0;
}

void PlayGameOn::execute()
{
}
