#include "tacticpush2goal.h"


TacticPush2Goal::TacticPush2Goal(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticPush2Goal", worldmodel, parent)
{
    circularBorder.assign(Vector2D(1500,0),1700/2);
    circularBorderOut.assign(Vector2D(1500,0),3700/2);
    hole1.assign(Vector2D(1500,1700/4),250);
    hole2.assign(Vector2D(1500,-1700/4),250);
}

RobotCommand TacticPush2Goal::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.loc=Vector2D(0,0);//circularBorder.center();
    rc.maxSpeed = 1.4;

    addData();
    sortData();


    for(int i=0;i<balls.size();i++)
    {

        c2o = new Segment2D(circularBorderOut.center() , balls.at(i) );
        temp=0;
        IsInside    =circularBorderOut.contains(balls.at(i));
        unAccessible=circularBorder   .contains(balls.at(i));

        if(!unAccessible)
        {
            index=i;
            qDebug() << "ACCESSIBLE" ;
            break;

        }
//        if(IsInside) qDebug()<< " INSIDE " ;
//        if(!IsInside) qDebug()<< "  OUT SIDE " ;
//        if(unAccessible) qDebug() << "UN - ACCESSIBLE" ;


    }


    Vector2D point2 = balls.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D nrstpnt = (circularBorderOut.center()-point2); //nearest Point
    nrstpnt=nrstpnt.setLength(nrstpnt.length()-circularBorderOut.radius());
    Vector2D diff2 = nrstpnt;
    nrstpnt=point2+nrstpnt;
    qDebug() << " X  = " << nrstpnt.x << "   Y =  " << nrstpnt.y;
    //Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    //qDebug() << " UN ACCESSIBLE :" << unAccessible ;

    if(!IsInside )
    {

        switch(state)
        {
        case 0:{ //Go Behind the Object

            Vector2D space2=diff2;
            space2.setLength(500);
            rc.maxSpeed=0.8;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - space2;
            rc.fin_pos.dir=diff2.dir().radian();//+M_PI;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
            if(reach) state = 1;

        }
            break;
        case 1:{//Ready to Push

            rc.useNav = false;
            rc.maxSpeed=1;
            diff2.setLength(200);
            rc.fin_pos.loc=point2 + diff2;
            rc.fin_pos.dir=diff2.dir().radian();//+M_PI;
            if(((wm->ourRobot[id].pos.loc-point2).length())>600) state=0;
        }
            break;

        }
    }
    else if(IsInside && !unAccessible)
    {
            Vector2D point2 = balls.at(index);
            Vector2D dist1 = balls.at(index)- hole1.center() ;
            Vector2D dist2 = balls.at(index)- hole2.center() ;
            if(dist2.length2()>dist1.length2())
            {
                vec2goal = (hole1.center() - point2);
            }
            else
            {
                vec2goal = (hole2.center() - point2);
            }


        switch(state2)
        {
        case 0:{ //Go Behind the Object

            vec2goal.setLength(300);
            qDebug()<<"VEC 2 GOAL LENGTH = " << vec2goal.length();
            rc.maxSpeed=1;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - vec2goal;
            rc.fin_pos.dir=vec2goal.dir().radian();
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
            if(reach) state2 = 1;

        }
            break;
        case 1:{//Ready to Push

            rc.useNav = false;
            rc.maxSpeed=3;
            vec2goal.setLength(400);
            rc.fin_pos.loc=point2  + vec2goal;
            rc.fin_pos.dir=vec2goal.dir().radian();
            if(((wm->ourRobot[id].pos.loc-point2).length())>500) state2=0;
            if(((wm->ourRobot[id].pos.loc-point2).length())<110) state2=0;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,40);
            if(reach)
            state2 = 0;
        }
            break;
        }

    }






    qDebug()<< "INDEX = " << index << "fin_pos.x  " << rc.fin_pos.loc.x << "  Y  "<<rc.fin_pos.loc.y<< " ------------------------------ STATE = " << state << "    STATE 2 =" << state2;

    //rc.fin_pos.loc=Vector2D(0,0);
    rc.maxSpeed = 1.2;
    rc.isBallObs = false;
    rc.isKickObs = true;
    return rc;
}
// ==================================================================================
void TacticPush2Goal::addData()
{

    balls.clear();
    balls.insert(0,wm->ball.pos.loc);//wm->ourRobot[0].pos.loc);
    balls.insert(1,wm->ourRobot[1].pos.loc);
    balls.insert(2,wm->ourRobot[2].pos.loc);

    //    agentsPositive.clear();
    //    agentsPositive.insert(0,wm->ourRobot[4].pos.loc);//wm->ourRobot[0].pos.loc);
    //    agentsPositive.insert(1,wm->ourRobot[5].pos.loc);

    //    agentsPositive.insert(2,wm->oppRobot[0].pos.loc);
}

// ==================================================================================
//Vector2D TacticPush2Goal::findnearest(Vector2D input)
//{
//    //int tmp = 0 ;
//    double dist;
//    Vector2D point=Vector2D(1000000,1000000);//,point2;
//    for(int k=0;k<segList.size();k++)
//    {
//        dist=(input-point).length2();
//        if((input-segList.at(k).nearestPoint(input)).length2()<dist) point=segList.at(k).nearestPoint(input);

//    }
//    return point;
//}


// ==================================================================================
void TacticPush2Goal::sortData()
{
    for(int i=0;i<balls.size();i++)
    {
        //for(int j=0;j<segList.size();j++)
        //{
        for(int k=i+1;k<balls.size();k++)
        {
            if( (balls.at(i)-circularBorder.center()).length2()
                    > (balls.at(k)-circularBorder.center()).length2() ) balls.swap(i,k);
        }
        //}

    }

}
// ==================================================================================
// ==================================================================================
