#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{

}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    testline=new Line2D(Vector2D(0,0),30);
    Line2D perp=testline->perpendicular(Vector2D(1,1));
    double doost=testline->dist(Vector2D(1,1));
    Vector2D proj=testline->projection(Vector2D(1,1));
    qDebug() << proj.length();//atan(perp.a()/perp.b())*180/M_PI;


    rc.maxSpeed = 1.2;
    rc.isBallObs = false;
    rc.isKickObs = true;
        return rc;
}
