#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    agentsForFirstRegion.push_back(wm->oppRobot[0].pos.loc);
    agentsForFirstRegion.append(wm->oppRobot[1].pos.loc);
    agentsForFirstRegion.append(wm->oppRobot[2].pos.loc);

    agentsForSecondRegion.append(wm->oppRobot[3].pos.loc);
    agentsForSecondRegion.append(wm->oppRobot[4].pos.loc);
    agentsForSecondRegion.append(wm->oppRobot[5].pos.loc);
}

RobotCommand TacticTest::getCommand()
{
//    RobotCommand rc;
//    if(!wm->ourRobot[id].isValid) return rc;

    //rc.maxSpeed = 2;

    //if(agentsForFirstRegion.isEmpty())
    //Position temp=agentsForFirstRegion.first();
    Vector2D point = agentsForFirstRegion.at(0);;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsForFirstRegion.first().loc;
    qDebug()<<"count:"<<agentsForFirstRegion.count();
    qDebug() << QString::number(point.x) << " ------- y : " << point.y ;


//    rc.useNav = true;
//    rc.isBallObs = false;
//    rc.isKickObs = true;
//    return rc;
}
