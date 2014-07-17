#include "tacticdefender.h"

TacticDefender::TacticDefender(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticDefender", worldmodel, parent)
{
    numberOfDefenders=NUMOFDEFENDERS;
}

RobotCommand TacticDefender::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    double ballDeg;
    double beta;
    double teta;
    double alpha=356;
    double gama;
    double dtgc;//distanceToGoldanCenter
    double dtgc2;
    double ballDistance;//ballDistanceToGoalCenter

    //Geometric calculations
    ballDeg=atan((wm->ball.pos.loc.y-0.0)/(wm->ball.pos.loc.x+(float)(Field::MaxX)));

    if(ballDeg>75.0*3.14/180)
    {
        ballDeg=75.0*3.14/180;
    }

    if(ballDeg<-75.0*3.14/180)
    {
        ballDeg=-75.0*3.14/180;
    }

    gama=AngleDeg::PI/2.0-abs(ballDeg);
    beta=asin((float)(Field::ourGoalPost_L.y)*sin(gama)/(2.0*Field::goalCircleEX_R));
    alpha=atan((float)(Field::ourGoalCC_L.y-Field::ourGoalCC_R.y)/(2.0*(float)(Field::goalCircleEX_R)));
    dtgc=(float)(Field::goalCircleEX_R)*sin(AngleDeg::PI-gama-beta)/sin(gama);
    dtgc2=sqrt(dtgc*dtgc+(float)(2*ROBOT_RADIUS+10)*(float)(2*ROBOT_RADIUS+10));
    teta=atan((float)(2*ROBOT_RADIUS+10)/dtgc);
    ballDistance=pow((pow(wm->ball.pos.loc.x+(float)(FIELD_MAX_X),2)+pow(wm->ball.pos.loc.y,2)),0.5);

    switch(position)
    {
    case CENTER:
        if(abs(ballDeg)<alpha)
        {
            rc.fin_pos.dir=ballDeg;
            rc.fin_pos.loc={-(float)(FIELD_MAX_X)+Field::goalCircleEX_R,0.0+tan(ballDeg)*Field::goalCircleEX_R};
        }

        else
        {
            rc.fin_pos.dir=ballDeg;
            rc.fin_pos.loc={-(float)(FIELD_MAX_X)+cos(ballDeg)*dtgc,0.0+sin(ballDeg)*dtgc};
        }
    break;

    case LEFT:
        rc.fin_pos.dir=ballDeg;
        rc.fin_pos.loc={-(float)(FIELD_MAX_X)+cos(ballDeg+teta)*dtgc2,0.0+sin(ballDeg+teta)*dtgc2};
        if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y>0)
        {
            if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
            {
                rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                rc.fin_pos.dir=ballDeg;
            }

            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 4))
            {

                if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
                {
                    rc.fin_pos.dir=ballDeg;
                }
                rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
            }

       }
    break;

    case RIGHT:
        rc.fin_pos.dir=ballDeg;
        rc.fin_pos.loc={-(float)(FIELD_MAX_X)+cos(ballDeg-teta)*dtgc2,0.0+sin(ballDeg-teta)*dtgc2};
        if(dtgc+2*ROBOT_RADIUS<ballDistance && ballDistance<dtgc+4*ROBOT_RADIUS && wm->ball.pos.loc.y<0)
        {
            if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 30, 180))
            {
                rc.fin_pos.loc= {wm->ball.pos.loc.x-110*cos(ballDeg),wm->ball.pos.loc.y-110*sin(ballDeg)};
                rc.fin_pos.dir=ballDeg;
            }

            if(wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 4))
            {

                if(!wm->kn->ReachedToPos(wm->ourRobot[id].pos, rc.fin_pos, 20, 2))
                {
                    rc.fin_pos.dir=ballDeg;
                }
                rc.fin_pos.loc= {wm->ball.pos.loc.x-100*cos(ballDeg),wm->ball.pos.loc.y-100*sin(ballDeg)};
            }
        }
    break;
    }

    rc.maxSpeed=1.5;

    rc.useNav = true;
    rc.isBallObs = true;
    rc.isKickObs = true;

    return rc;
}

void TacticDefender::setDefenderPos(int pos)
{
    this->position=pos;
}
