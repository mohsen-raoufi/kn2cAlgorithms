#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    circularBorder.assign(Vector2D(1500,0),1700/2);
    circularBorderOut.assign(Vector2D(1500,0),3700/2);
    hole1.assign(Vector2D(1500,1700/4),250);
    hole2.assign(Vector2D(1500,-1700/4),250);
}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.loc=Vector2D(0,0);//circularBorder.center();
    rc.maxSpeed = 1.4;

    addData();
    sortData();

    //   qDebug() << wm->ball.pos.loc.x<< "------ Y = " << wm->ball.pos.loc.y ;


    for(int i=0;i<balls.size();i++)
    {

        c2o = new Segment2D(circularBorderOut.center() , balls.at(i) );
        temp=0;
        IsInside    =circularBorderOut.contains(balls.at(i));
        unAccessible=circularBorder   .contains(balls.at(i));
        //        for(int j=0;j<segList.size(); j++)
        //        {
        //            if(segList.at(j).existIntersection(*o2o))
        //            {
        //                IsOverTheLine=true;
        //                break;
        //            }

        //        }



        if(!unAccessible)
        {
            index=i;
            qDebug() << "ACCESSIBLE" ;
            //if(IsInside) qDebug()<< " INSIDE " ;
            //qDebug() << "TOOOOOOOOOOOOOOOOOOOSHE !!!!!!!" << index ;//balls.at(i).x << " Y ---- " << balls.at(i).y;//
            //goalRegion=agentsNegative.at(i).goalRegion;
            // (((())))temp=1;
            //break;

        }
        if(IsInside) qDebug()<< " INSIDE " ;
        if(!IsInside) qDebug()<< "  OUT SIDE " ;
        if(unAccessible) qDebug() << "UN - ACCESSIBLE" ;

//        else if(unAccessible)
//        {
//            qDebug()<<"!!!!!!!!!!! UN ACCCC EEEEEE SSSSS IIIII BBB LLLL EEEE !!!!!!!!!!!!!!!!!!";
//        }

    }


    Vector2D point2 = balls.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D nrstpnt = (circularBorderOut.center()-point2); //nearest Point
    nrstpnt=nrstpnt.setLength(nrstpnt.length()-circularBorderOut.radius());
    Vector2D diff2 = nrstpnt;
    nrstpnt=point2+nrstpnt;
    qDebug() << " X  = " << nrstpnt.x << "   Y =  " << nrstpnt.y;
    //Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    // agentsNegative.
    qDebug() << " UN ACCESSIBLE :" << unAccessible ;
    //if(!unAccessible)
    //{
    if(!IsInside )
    {

        switch(state)
        {
        case 0:{ //Go Behind the Object

            Vector2D space2=diff2;
            //int side = agentsNegative.at(index).goalRegion;
            space2.setLength(500);
            //space2.setDir(space2.dir() + M_PI*side);
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
            //rc.fin_pos.loc.x=point2.x +50*(diff2.x)/(diff2.length());
            //rc.fin_pos.loc.y=point2.y +50*(diff2.y)/(diff2.length());
            rc.fin_pos.dir=diff2.dir().radian();//+M_PI;
            if(((wm->ourRobot[id].pos.loc-point2).length())>600) state=0;
//            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,30);
//            if(reach)
//                state = 2;
        }
            break;
//        case 2:{//Push
//            //Vector2D diff2 = region2.center() - wm->ourRobot[id].pos.loc ;
//            rc.useNav = false;
//            if(diff2.length() > 1500) diff2.setLength(1500);
//            if(((wm->ourRobot[id].pos.loc-point2).length())>300) state=0;
//            if(((wm->ourRobot[id].pos.loc-point2).length())<180) state=0;
//            rc.fin_pos.loc=point2 - diff2/5;
//            rc.fin_pos.dir=diff2.dir().radian()+M_PI;
//            //            reach=testseg->existIntersection(*o2o);//wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
//            //            if(reach)
//            //            {
//            //                state = 3;
//            //                qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
//            //                count++;
//            //                if(temp==0)
//            //                {
//            //                    rc.fin_pos.loc=origin;//Vector2D(1500,1500);
//            //                    break;
//            //                }
//            //            }
//        }
//            break;

        }
    }
    else if(IsInside && !unAccessible)
    {
        //for(int i=0;i<100;i++)
        //{
            Vector2D point2 = balls.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
            Vector2D dist1 = balls.at(index)- hole1.center() ;
            Vector2D dist2 = balls.at(index)- hole2.center() ;
            if(dist2.length2()>dist1.length2())
            {
                vec2goal = (hole1.center() - point2);
                //vec2goal=vec2goal.setLength(150);
                //nrstpnt=point2+nrstpnt;
            }
            else
            {
                vec2goal = (hole2.center() - point2);
                //vec2goal=vec2goal.setLength(150);
                //nrstpnt=point2+nrstpnt;
            }


            //        Vector2D vec2goal= wm->ourRobot[id].pos.loc - circularBorder.center();
            //        vec2goal.setDir(vec2goal.dir()+5);
            //        vec2goal.setLength(1200);
            //        qDebug()<<"===============================================================" << vec2goal.dir().degree();
            //        rc.fin_pos.loc= circularBorder.center() + vec2goal; //wm->ourRobot[id].pos.loc + vec2goal
            //        rc.maxSpeed=10;
            //        rc.fin_pos.dir=vec2goal.dir().radian()+M_PI;
        //}

        switch(state2)
        {
        case 0:{ //Go Behind the Object

            //Vector2D space2=diff2;
            //int side = agentsNegative.at(index).goalRegion;
            vec2goal.setLength(300);
            qDebug()<<"VEC 2 GOAL LENGTH = " << vec2goal.length();
            //space2.setDir(space2.dir() + M_PI*side);
            rc.maxSpeed=1;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - vec2goal;//Vector2D(1000,1000);//
            rc.fin_pos.dir=vec2goal.dir().radian();
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
            if(reach) state2 = 1;

        }
            break;
        case 1:{//Ready to Push

            rc.useNav = false;
            rc.maxSpeed=3;
            //int side = -1;//agentsNegative.at(index).goalRegion;
            vec2goal.setLength(400);
            rc.fin_pos.loc=point2  + vec2goal;
            //rc.fin_pos.loc.x=point2.x -50*(vec2goal.x)/(vec2goal.length());
            //rc.fin_pos.loc.y=point2.y -50*(vec2goal.y)/(vec2goal.length());
            rc.fin_pos.dir=vec2goal.dir().radian();
            if(((wm->ourRobot[id].pos.loc-point2).length())>500) state2=0;
            if(((wm->ourRobot[id].pos.loc-point2).length())<110) state2=0;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,40);
            if(reach)
            state2 = 0;
        }
            break;
//        case 2:{//Push
//            //Vector2D diff2 = region2.center() - wm->ourRobot[id].pos.loc ;
//            rc.useNav = false;
//            if(diff2.length() > 1500) diff2.setLength(1500);
//            if(((wm->ourRobot[id].pos.loc-point2).length())>300) state=0;
//            if(((wm->ourRobot[id].pos.loc-point2).length())<180) state=0;
//            rc.fin_pos.loc=point2 + diff2/5;
//            rc.fin_pos.dir=diff2.dir().radian();
            //            reach=testseg->existIntersection(*o2o);//wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
            //            if(reach)
            //            {
            //                state = 3;
            //                qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
            //                count++;
            //                if(temp==0)
            //                {
            //                    rc.fin_pos.loc=origin;//Vector2D(1500,1500);
            //                    break;
            //                }
            //            }
       // }
           // break;

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
void TacticTest::addData()
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
            if( (balls.at(i)-circularBorder.center()).length2()
                    > (balls.at(k)-circularBorder.center()).length2() ) balls.swap(i,k);
        }
        //}

    }

}
// ==================================================================================
// ==================================================================================
