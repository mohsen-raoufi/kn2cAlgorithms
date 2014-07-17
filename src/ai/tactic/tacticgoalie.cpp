#include "tacticgoalie.h"

TacticGoalie::TacticGoalie(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticGoalie", worldmodel, parent)
{
}

RobotCommand TacticGoalie::getCommand()
{
        RobotCommand rc;

        double ballDeg;
        double ballDir;
        double yInGoal;


        //Geometric calculations
        ballDeg=atan((wm->ball.pos.loc.y-0.0)/(wm->ball.pos.loc.x+(float)(FIELD_MAX_X)));
        ballDir=(float)(wm->ball.vel.loc.y)/(float)(wm->ball.vel.loc.x);
        yInGoal=wm->ball.pos.loc.y-ballDir*(float)((float)(FIELD_MAX_X)+wm->ball.pos.loc.x);

        if(((wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y<0) || (wm->ball.vel.loc.x<0 && wm->ball.vel.loc.y>0)) && (abs(yInGoal)<350))
        {
         rc.fin_pos.loc={-(float)(FIELD_MAX_X)+ROBOT_RADIUS,yInGoal};
         rc.fin_pos.dir=ballDeg;
        }
        else
        {
            rc.fin_pos.loc={-(float)(FIELD_MAX_X)+ROBOT_RADIUS,0};
            rc.fin_pos.dir=ballDeg;
        }
        //qDebug()<<ballDeg*180.0/3.14<<beta<<alpha<<dtgc;


        rc.maxSpeed=7;

        rc.useNav = true;
        rc.isBallObs = true;
        rc.isKickObs = true;

        return rc;
}

