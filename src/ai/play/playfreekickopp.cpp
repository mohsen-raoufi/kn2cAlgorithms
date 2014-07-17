#include "playfreekickopp.h"

PlayFreeKickOpp::PlayFreeKickOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOpp", worldmodel, parent)
{
}

int PlayFreeKickOpp::enterCondition()
{
    if(wm->cmgs.theiFreeKick() || wm->cmgs.theirDirectKick())
        return 100;
    else
        return 0;

    return 0;
}

void PlayFreeKickOpp::execute()
{
}
