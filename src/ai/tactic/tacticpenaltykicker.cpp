#include "tacticpenaltykicker.h"

TacticPenaltyKicker::TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent) :
    TacticAttacker(worldmodel)
{
    this->setObjectName("TacticPenaltyKicker");
}

RobotCommand TacticPenaltyKicker::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc=goBehindBall();

    rc.maxSpeed=0.5;
    rc.useNav=true;
    rc.isBallObs=true;
    rc.isKickObs=true;

    if(canKick)
    {
        rc.maxSpeed=0;
        if(wm->cmgs.canKickBall())
        {
            rc.kickspeedx=255;
        }
    }
    return rc;
}
