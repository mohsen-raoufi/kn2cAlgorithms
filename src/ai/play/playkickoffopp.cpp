#include "playkickoffopp.h"

PlayKickoffOpp::PlayKickoffOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayKickoffOpp", worldmodel, parent)
{
}

int PlayKickoffOpp::enterCondition()
{
    if(wm->cmgs.theirKickoff())
        return 100;
    else
        return 0;
}

void PlayKickoffOpp::execute()
{
}
