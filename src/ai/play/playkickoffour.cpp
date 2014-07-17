#include "playkickoffour.h"

PlayKickoffOur::PlayKickoffOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOur", worldmodel, parent)
{
}

int PlayKickoffOur::enterCondition()
{
    if(wm->cmgs.ourKickoff())
        return 100;
    else
        return 0;
}

void PlayKickoffOur::execute()
{

}
