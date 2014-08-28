#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    circularBorder.assign(Vector2D(1500,0),1700/2);
    circularBorderOut.assign(Vector2D(1500,0),2100/2);// a circle may use to push balls with some risks
    circularMid.assign(Vector2D(1500,0),720); // a circle which is between holes and border circle
    hole1.assign(Vector2D(1500,1700/4),250);
    hole2.assign(Vector2D(1500,-1700/4),250);
    Vector2D Cdist = (hole1.center() - circularBorder.center());
    double deltaAngle=1.1*asin(hole1.radius()/(Cdist.length())); // 1.1 is safety factor
    Uangle1=Cdist.dir().radian() + deltaAngle ;
    Dangle1=Uangle1 - 2*deltaAngle;
    Cdist = (hole2.center() - circularBorder.center());
    Uangle2=Cdist.dir().radian() + deltaAngle ;
    Dangle2=Uangle2 - 2*deltaAngle;

}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.loc=circularBorder.center(); //
    rc.maxSpeed = 1.4;

    addData();
    //sortData();
    //qDebug()<< " U 1 =" << Uangle1 << "   D 1 =" << Dangle1 << " /////// U2 = " << Uangle2 << "   D2 = " << Dangle2 ;
    //qDebug() << " ANGLE     = " << (circularBorder.center()-balls.at(0)).dir().radian();
    for(int i=0;i<balls.size();i++)
    {
        AllIn=true;
        AnyIn=false;
        //c2o = new Segment2D(circularBorderOut.center() , balls.at(i) );
        //temp=0;
        IsInside   = circularBorder  .contains(balls.at(i)->pos.loc);
        Accessible = circularBorderOut.contains(balls.at(i)->pos.loc);

        if(!IsInside) AllIn = false;
        else if(IsInside) AnyIn = true;
        index=i;

    }
    Vector2D vel=balls.at(index)->vel.loc;
    qDebug() << "ball's velocity = " << vel.length() ;
    point = findnearest2circle(); //balls.at(index);
    ballVel = new Line2D(point , vel.dir().degree());
    //ballVel = new Line2D(point , vel.dir().degree());
    towardH1 = hole1.HasIntersection(*ballVel,1.3);
    towardH2 = hole2.HasIntersection(*ballVel,1.3);
    float minVel=0.4;

    if((!towardH1 && !towardH2) || (vel.length() < minVel))
    {

        //qDebug() << " POINT . X = "  <<  point.x << "          POINT . Y =" << point.y;
        //        Vector2D nrstpnt = (point - circularBorderOut.center());//findnearesthole(point));//
        //        rc.fin_pos.dir = nrstpnt.dir().radian() ;
        //        nrstpnt=nrstpnt.setLength(circularMid.radius()-70);//300);//
        //        //Vector2D diff = nrstpnt;
        //        nrstpnt=nrstpnt + circularBorderOut.center();//findnearesthole(point) ;//
        //        //qDebug() << " X  = " << nrstpnt.x << "   Y =  " << nrstpnt.y;
        //        rc.fin_pos.loc=nrstpnt;//goOncircle2point(nrstpnt);


        if(!oppIsInField && !AnyIn)
        {
            state=1;
            //qDebug() << " ANYIN is FFFFFFFFFFFFFFALSE";

                //qDebug() << " POINT . X = "  <<  point.x << "          POINT . Y =" << point.y;
                Vector2D nrstpnt = (point - circularBorderOut.center());//findnearesthole(point));//
                rc.fin_pos.dir = nrstpnt.dir().radian() ;
                nrstpnt=nrstpnt.setLength(circularMid.radius()-70);//300);//
                //Vector2D diff = nrstpnt;
                nrstpnt=nrstpnt + circularBorderOut.center();//findnearesthole(point) ;//
                //qDebug() << " X  = " << nrstpnt.x << "   Y =  " << nrstpnt.y;
                rc.fin_pos.loc=nrstpnt;//goOncircle2point(nrstpnt);

        }

        else if(!oppIsInField && AnyIn)
        {
            state=10;
            //qDebug() << " ANYIN is TRUE ";
            point = balls.at(index)->pos.loc;
            Vector2D nrstpnt = circularBorder.center()-point;//findnearesthole(point)-point);
            Line2D ball2center(point,circularBorder.center());
            double ang=nrstpnt.dir().radian();
            //if (!(((ang < Uangle1 && ang > Dangle1) || (ang < Uangle2 && ang > Dangle2) ) && (nrstpnt.length2() < (circularBorder.center()-hole1.center()).length2())))//&& ang < Dangle1 && ang < Dangle2)
            if((hole1.HasIntersection(ball2center) || hole2.HasIntersection(ball2center)) && (nrstpnt.length2() < 1.1*(circularBorder.center()-hole1.center()).length2()) )
            {
                state=101;
                qDebug() << " NAKON TOO SOoooooooooooooooooooooORAAKH !!!";
                nrstpnt.setDir(nrstpnt.dir()+90);//M_PI/2);
                nrstpnt.setLength(150);
                rc.fin_pos.dir=nrstpnt.dir().radian()+M_PI;
                nrstpnt=point+nrstpnt;
                rc.fin_pos.loc=nrstpnt;
                bool reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
                if(reach)
                {
                    nrstpnt = point - nrstpnt;
                    nrstpnt.setLength(150);
                    rc.fin_pos.dir=nrstpnt.dir().radian();//+M_PI;
                    nrstpnt = point + nrstpnt;
                    rc.fin_pos.loc=nrstpnt;
                    rc.useNav=false;
                }
                //rc.fin_pos.loc=circularBorder.center();
            }
            else
            {
                state=102;
                //qDebug() << ang ;
                qDebug() << " biroon SOORAAKH !!!";

                nrstpnt.setDir(nrstpnt.dir());//+M_PI/2);
                nrstpnt.setLength(150);
                rc.fin_pos.dir=nrstpnt.dir().radian()+M_PI;
                nrstpnt=point+nrstpnt;
                rc.fin_pos.loc=nrstpnt;
                //rc.fin_pos.dir=nrstpnt.dir().radian();//+M_PI;
                bool reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,20);
                if(reach)
                {
                    nrstpnt = point - nrstpnt;
                    nrstpnt.setLength(150);
                    rc.fin_pos.dir=nrstpnt.dir().radian();//+M_PI;
                    nrstpnt = point + nrstpnt;
                    rc.fin_pos.loc=nrstpnt;
                    //rc.fin_pos.dir=nrstpnt.dir().radian()+M_PI;
                    rc.useNav=false;
                }
            }


        }
    }
    else if(towardH1 && !towardH2 && (vel.length() > minVel) )
    {
        state=2;
        qDebug() << " TOWARD HOLE # 1";
        Vector2D nrstpnt = (point - hole1.center());
        rc.fin_pos.dir = nrstpnt.dir().radian() ;
        nrstpnt=nrstpnt.setLength(hole1.radius()+ROBOT_RADIUS + 50);//circularMid.radius());//
        nrstpnt=nrstpnt + hole1.center();//findnearesthole(point) ;//
        rc.fin_pos.loc=nrstpnt;
    }
    else if(towardH2 && !towardH1 && (vel.length() > minVel) )
    {
        state=3;
        qDebug() << " TOWARD HOLE # 2";
        Vector2D nrstpnt = (point - hole2.center());
        rc.fin_pos.dir = nrstpnt.dir().radian() ;
        nrstpnt=nrstpnt.setLength(hole2.radius()+ROBOT_RADIUS + 50);//circularMid.radius());//
        nrstpnt=nrstpnt + hole2.center();//findnearesthole(point) ;//
        rc.fin_pos.loc=nrstpnt;
    }
    else if(towardH1 && towardH2 && (vel.length() > minVel) )
    {
        state=4;
        Vector2D distH1 = (point - hole1.center());
        Vector2D distH2 = (point - hole2.center());
        if(distH1.length2() < distH2.length2())
        {
            distH1.setLength(hole1.radius() + ROBOT_RADIUS + 50);
            rc.fin_pos.loc = hole1.center() + distH1 ;
            rc.fin_pos.dir = distH1.dir().radian();
        }
        else
        {
            distH2.setLength(hole2.radius() + ROBOT_RADIUS + 50);
            rc.fin_pos.loc = hole2.center() + distH2 ;
            rc.fin_pos.dir = distH2.dir().radian();
        }
    }
    //Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
    //bool reach=false;

    //qDebug()<< "INDEX = " << index << "fin_pos.x  " << rc.fin_pos.loc.x << "  Y  "<<rc.fin_pos.loc.y<< " ------------------------------ STATE = " << state << "    STATE 2 =" << state2;
    qDebug() << " S T A T E  =  " << state;
    //qDebug() << "                                     ANY IN " << AnyIn ;
    //rc.fin_pos.loc=Vector2D(0,0);
    rc.maxSpeed = 1.1;
    rc.isBallObs = false;
    rc.isKickObs = true;
    return rc;
}
// ==================================================================================
void TacticTest::addData()
{

    balls.clear();
    balls.insert(0,&wm->ball);//wm->ourRobot[0].pos.loc);

    //balls.insert(1,&wm->ourRobot[1]);
    //balls.insert(2,wm->ourRobot[2].pos.loc);

    oppIsInField = wm->oppRobot[4].isValid;
    OppositeRobot = wm->oppRobot[4].pos.loc;
}

// ==================================================================================
//Vector2D TacticTest::findnearest(Vector2D input)
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
void TacticTest::sortData()
{
    for(int i=0;i<balls.size();i++)
    {
        //for(int j=0;j<segList.size();j++)
        //{
        for(int k=i+1;k<balls.size();k++)
        {
            if( (balls.at(i)->pos.loc-circularBorder.center()).length2()
                    > (balls.at(k)->pos.loc-circularBorder.center()).length2() ) balls.swap(i,k);
        }
        //}

    }

}
// ==================================================================================
void TacticTest::goOncircle2point(Vector2D pnt)
{

}

// =================================================================================
Vector2D TacticTest::findnearest2circle()
{
    int tmp=0;
    for(int k=0;k<balls.size();k++)
    {
        if( (balls.at(k)->pos.loc-circularBorder.center()).length2() < (balls.at(tmp)->pos.loc-circularBorder.center()).length2()) tmp=k;
    }
    return balls.at(tmp)->pos.loc;
}
// ==================================================================================
Vector2D TacticTest::findnearesthole(Vector2D pnt)
{
    if( (pnt-hole1.center()).length2() < (pnt-hole2.center()).length2() ) return hole1.center();
    else return hole2.center();
}
// ==================================================================================
// ==================================================================================
