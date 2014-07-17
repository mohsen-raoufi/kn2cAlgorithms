#include "playfreekickour.h"

PlayFreeKickOur::PlayFreeKickOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayFreeKickOur", worldmodel, parent)
{
}

int PlayFreeKickOur::enterCondition()
{
    if(wm->cmgs.ourFreeKick() || wm->cmgs.ourIndirectKick())
        return 100;
    else
        return 0;

    return 0;
}

void PlayFreeKickOur::execute()
{

}
