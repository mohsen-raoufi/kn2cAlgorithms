#include "tacticpush2goal.h"


TacticPush2Goal::TacticPush2Goal(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticPush2Goal", worldmodel, parent)
{
    circularBorder      .assign(Vector2D(1500,0),(1700/2));//+ROBOT_RADIUS);
    circularBorderOut   .assign(Vector2D(1500,0),(1750));
    circularBorderDANGER.assign(Vector2D(1500,0),circularBorder.radius()+ROBOT_RADIUS+200);
    circularBorder2     .assign(Vector2D(1500,0),circularBorder.radius()+ROBOT_RADIUS+100);
    hole1.assign(Vector2D(1500,1700/4),250);
    hole2.assign(Vector2D(1500,-1700/4),250);
    DontEnterCircle=true;
}

RobotCommand TacticPush2Goal::getCommand()
{

    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    //rc.fin_pos.loc=Vector2D(0,0);//circularBorder.center();
    rc.maxSpeed = 1.4;

    addData();
    sortData();

    rc.fin_pos.loc=circularBorder2.nearestpoint(balls.at(balls.size()-1));

    for(int i=0;i<balls.size();i++)
    {

        c2o = new Segment2D(circularBorderOut.center() , balls.at(i) );
        temp=0;
        IsInside    =circularBorderOut.contains(balls.at(i));
        unAccessible=circularBorder   .contains(balls.at(i));

        if(!unAccessible)
        {
            index=i;
            qDebug() << "ACCESSIBLE"  ;
            break;

        }
        //        if(IsInside) qDebug()<< " INSIDE " ;
        //        if(!IsInside) qDebug()<< "  OUT SIDE " ;
        //        if(unAccessible) qDebug() << "UN - ACCESSIBLE" ;


    }

    //qDebug() << "IS INSIDE = " << IsInside <<
    Vector2D point2 = balls.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D nrstpnt = (circularBorderOut.center()-point2); //nearest Point
    nrstpnt=nrstpnt.setLength(nrstpnt.length()-circularBorderOut.radius());
    diff2 = nrstpnt;
    nrstpnt=point2+nrstpnt;
    //qDebug() << " X  = " << nrstpnt.x << "   Y =  " << nrstpnt.y;
    //Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    //qDebug() << " UN ACCESSIBLE :" << unAccessible ;

    if(!IsInside )
    {
        qDebug() << " FIRST IF";
        state2=0;
        switch(state)
        {
        case 0:{ //Go Behind the Object

            Vector2D space2=diff2;
            space2.setLength(200);
            rc.maxSpeed=1.2;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - space2;
            rc.fin_pos.dir=diff2.dir().radian();//+M_PI;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,100);
            if(reach) state = 1;

        }
            break;
        case 1:{//Ready to Push
            //qDebug()<<" STATE IS NOT ZERO !!!";
            rc.useNav = false;
            rc.maxSpeed=1;
            diff2.setLength(200);
            rc.fin_pos.loc=point2 + diff2;
            rc.fin_pos.dir=diff2.dir().radian();//+M_PI;
            if(((wm->ourRobot[id].pos.loc-point2).length())>800) {
                state=0;
                qDebug() << " hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh ";
            }
            if(((wm->ourRobot[id].pos.loc-point2).length())<ROBOT_RADIUS+BALL_RADIUS) state=0;
            if(((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length())<20) state=0;
        }
            break;

        }
    }
    else if(IsInside && !unAccessible)
    {
        state=0;
        qDebug() << " SECOND IFFFFFFFFF" ;
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

            vec2goal.setLength(400);
            qDebug()<<"VEC 2 GOAL LENGTH = " << vec2goal.length();
            rc.maxSpeed=1;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - vec2goal;
            rc.fin_pos.dir=vec2goal.dir().radian();
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
            if(reach) state2 = 1;

        }
            break;
        case 1:{//Push

            rc.useNav = false;
            rc.maxSpeed=1.1;
            vec2goal.setLength(300);
            rc.fin_pos.loc=point2  + vec2goal;
            rc.fin_pos.dir=vec2goal.dir().radian();
            if(((wm->ourRobot[id].pos.loc-point2).length())>700) state2=0;
            if(((wm->ourRobot[id].pos.loc-rc.fin_pos.loc).length())<50) state2=0;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,40);
            if(reach)
                state2 = 0;
        }
            break;
        }

    }
        else if(IsInside && unAccessible )
        {
            //qDebug()<<"GO ON CIRCLE !!!! ";
            //rc.fin_pos.loc=GoOncircle(circularBorder.center(),1100);//circularBorderOut.radius());//,wm->ourRobot[id].pos.loc);
            Vector2D diff=wm->ourRobot[id].pos.loc-circularBorder.center();
            rc.fin_pos.dir=diff.dir().radian()+M_PI;
        }



    if(DontEnterCircle && circularBorderDANGER.contains(wm->ourRobot[id].pos.loc) && circularBorder2.contains(point2))//circularBorderDANGER.contains(rc.fin_pos.loc))
    {
        rc.fin_pos.loc=circularBorderDANGER.nearestpoint(point2);//wm->ourRobot[id].pos.loc;//AvoidtoEnterCircle(circularBorderDANGER,point2);
        rc.maxSpeed=1.1;
    }

    qDebug()<< "BEFOR ANY CHANGE " << "fin_pos.x  " << rc.fin_pos.loc.x << "  Y  "<<rc.fin_pos.loc.y<< " ------------------------------ STATE = " << state << "    STATE 2 =" << state2;
//    qDebug()<< "          " << "ROBOT POS.x  " << wm->ourRobot[id].pos.loc.x << "  Y  "<< wm->ourRobot[id].pos.loc.y;
//    qDebug() << "Distance To Fin_Pos =  " << (rc.fin_pos.loc-wm->ourRobot[id].pos.loc).length();
//    //rc.fin_pos.loc=Vector2D(0,0);
    //rc.maxSpeed = 1.2;
    rc.fin_pos.loc=AvoidtoEnterCircle(circularBorder2,wm->ourRobot[id].pos.loc,rc.fin_pos.loc);//rc.fin_pos.loc);
    bool rich = wm->kn->ReachedToPos(wm->ourRobot[id].pos,rc.fin_pos,10,5);
    if(rich) rc.fin_pos.loc=wm->ourRobot[id].pos.loc;
    qDebug() << " DIRECTION ERROR =     " << (rc.fin_pos.dir-wm->ourRobot[id].pos.dir)*(180/3.14);
    //rc.useNav = true;
    rc.maxSpeed=1.5*rc.maxSpeed;
    rc.isBallObs = false;
    rc.isKickObs = true;

    qDebug()<< "INDEX = " << index << "fin_pos.x  " << rc.fin_pos.loc.x << "  Y  "<<rc.fin_pos.loc.y<< " ------------------------------ STATE = " << state << "    STATE 2 =" << state2;
    qDebug()<< "          " << "ROBOT POS.x  " << wm->ourRobot[id].pos.loc.x << "  Y  "<< wm->ourRobot[id].pos.loc.y;
    //qDebug() << "Distance To Fin_Pos =  " << (rc.fin_pos.loc-wm->ourRobot[id].pos.loc).length();


    return rc;
}
// ==================================================================================
void TacticPush2Goal::addData()
{

    balls.clear();
    balls.insert(0,wm->ball.pos.loc);//wm->ourRobot[0].pos.loc);
    //balls.insert(1,wm->ourRobot[1].pos.loc);
    //balls.insert(2,wm->ourRobot[2].pos.loc);

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
// =================================================================================
Vector2D TacticPush2Goal::GoOncircle(Vector2D center, double radius)//, Vector2D Object)
{
    //for (int k=0;k<1000;k++)

    Vector2D diff = wm->ourRobot[id].pos.loc - center;
    diff.setDir(diff.dir()+1.1);//50);//.radian() + AngleDeg::deg2rad(5));
    diff.setLength(radius);
    Vector2D point = center + diff;
    return point;

}
// =================================================================================
Vector2D TacticPush2Goal::AvoidtoEnterCircle(Circle2D Ci,Vector2D pnt , Vector2D finPOS)
{
    Segment2D S(pnt,finPOS);
    if(Ci.HasIntersection(S))
    {
        //qDebug() << " HAS INTERSECTION WITH CIRCLE !! DO NOT ENTER THIS CIRCLE PLEASE !!!";
        Vector2D c2r = pnt - Ci.center() ;
        Vector2D c2f = finPOS - Ci.center() ;
        c2r.setLength(Ci.radius()+50);
        AngleDeg angle=c2r.dir() - c2f.dir();
        //double ang=c2r.dir().radian() - c2f.dir().radian();
        if (angle.radian() > M_PI) angle -=  AngleDeg(M_PI) *= 2;
        if (angle.radian() < -M_PI) angle += AngleDeg(M_PI) *= 2;

        //if (ang > M_PI) ang -= 2 * M_PI;
        //if (ang < -M_PI) ang += 2 * M_PI;

        //qDebug() << "c2r DIRECTION = " << c2r.dir().degree() << "c2f DIRECTION = " << c2f.dir().degree() << "   ANGLE  = " << angle.degree() << "    ANG =" << ang*57.32;
        angle=angle/=6;
        angle=c2r.dir() - angle;
        c2r.setDir(angle);// c2f.dir()));
        Vector2D p = Ci.center() + c2r ;
        return p;
    }
    else
    {
        return finPOS;
    }
}

// ==================================================================================
// ==================================================================================
