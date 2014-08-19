#include "tacticconfront.h"

TacticConfront::TacticConfront(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticConfront", worldmodel, parent)
{
    count=0;
    origin=Vector2D(1500,0);
    origin2=Vector2D(-1500,0);
    obs=0;
}

RobotCommand TacticConfront::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.loc=origin;
    rc.maxSpeed = 1.4;


    addData();
    addseg();
    //mergeData();
    sortData();


    //Line2D segline = testseg->line();
    //double y=segline.getX(500);
    //qDebug() << y;

    //    Vector2D proj=testseg->nearestPoint(wm->ball.pos.loc);
    //    qDebug() << proj.x<< "------ Y = " << proj.y ; // length();//atan(perp.a()/perp.b())*180/M_PI;
    //   qDebug() << wm->ball.pos.loc.x<< "------ Y = " << wm->ball.pos.loc.y ;
    //    testseg->existIntersection();

    //---------------------------TRANSFER NEGATIVE OBJECTS OVER THE LINE ---------------
    for(int i=0;i<agentsNegative.size();i++)
    {
        //if(obstacle)wm->kn->)
        //{continue; }
        //origin.x=origin.x*(2*agentsNegative.at(i).goalRegion - 1 );
        o2o = new Segment2D(origin , agentsNegative.at(i) );
        temp=0;
        bool IsOverTheLine=false;
        for(int j=0;j<segList.size(); j++)
        {
            if(segList.at(j).existIntersection(*o2o))
            {
                IsOverTheLine=true;
                break;
            }

        }

        //if(IsOverTheLine) break;

        if(!IsOverTheLine)
        {
            index=i;
            //qDebug() << 2*agentsNegative.at(i).goalRegion - 1 ;
            qDebug() << agentsNegative.at(i).x << " Y ---- " << agentsNegative.at(i).y;// TOOOOOOOOOOOOOOOOOOOSHE !!!!!!!" << index ;
            //goalRegion=agentsNegative.at(i).goalRegion;
            temp=1;
            break;
        }

    }


    Vector2D point2 = agentsNegative.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D nrstpnt = findnearest(point2);
    Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    // agentsNegative.

    if(temp!=0)
    {
        switch(state)
        {
        case 0:{ //Go Behind the Object

            Vector2D space2=diff2;
            //int side = agentsNegative.at(index).goalRegion;
            space2.setLength(300);
            //space2.setDir(space2.dir() + M_PI*side);
            rc.maxSpeed=0.8;
            rc.useNav = true;
            rc.fin_pos.loc=point2  - space2;
            rc.fin_pos.dir=diff2.dir().radian();
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
            if(reach) state = 1;

        }
            break;
        case 1:{//Ready to Push

            rc.useNav = false;
            rc.maxSpeed=0.4;
            int side = -1;//agentsNegative.at(index).goalRegion;
            rc.fin_pos.loc.x=point2.x +(side)*100*(diff2.x)/(diff2.length());
            rc.fin_pos.loc.y=point2.y +(side)*100*(diff2.y)/(diff2.length());
            rc.fin_pos.dir=diff2.dir().radian();
            if(((wm->ourRobot[id].pos.loc-point2).length())>400) state=0;
            reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
            if(reach)
                state = 2;
        }
            break;
        case 2:{//Push
            //Vector2D diff2 = region2.center() - wm->ourRobot[id].pos.loc ;
            rc.useNav = false;
            if(diff2.length() > 1500) diff2.setLength(1500);
            if(((wm->ourRobot[id].pos.loc-point2).length())>300) state=0;
            if(((wm->ourRobot[id].pos.loc-point2).length())<180) state=0;
            rc.fin_pos.loc=point2 + diff2/5;
            rc.fin_pos.dir=diff2.dir().radian();
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
        }
            break;
        case 3:{//Release

            // if(testseg->existIntersection(*o2o))
            //{
            qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
            count++;
            //if(index==agentsR1.size()) rc.fin_pos.loc=Vector2D(0,0);
            if(temp==0)
            {
                rc.fin_pos.loc=origin;//Vector2D(1500,1500);
                break;
            }
            //agentsR1.takeFirst();
            //index++;
            // }
            //if(reach)
            state = 0;
        }
            break;
        }
    }
    // ---------------------------------------------------------------------------------

    //--------------------------TRANSFER POSITIVE OBJECTS OVER THE LINE ----------------
    if(temp==0)
    {
        for(int i=0;i<agentsPositive.size();i++)
        {
            //if(obstacle)wm->kn->)
            //{continue; }
            //r2o = new Segment2D(Vector2D(wm->ourRobot[id].pos.loc) , Vector2D(agentsPositive.at(i).pos));
            //qDebug() << 2*agentsPositive.at(i).goalRegion - 1 ;
            o2o = new Segment2D(origin2 , Vector2D(agentsPositive.at(i)));
            temp2=0;
            IsOverTheLine=false;
            for(int j=0;j<segList.size(); j++)
            {
                if(segList.at(j).existIntersection(*o2o))
                {
                    IsOverTheLine=true;
                    break;
                }

            }

            if(!IsOverTheLine || agentsPositive.at(i).x < origin.x)
            {
                index=i;
                qDebug() << agentsPositive.at(i).x << " Y ---- " << agentsPositive.at(i).y;// TOOOOOOOOOOOOOOOOOOOSHE !!!!!!!" << index ;
                //goalRegion=agentsPositive.at(i).goalRegion;
                temp2=1;
                break;
            }

        }


        Vector2D point2 = agentsPositive.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
        Vector2D nrstpnt = findnearest(point2);
        Vector2D diff2 = nrstpnt - point2;// wm->ourRobot[id].pos.loc ;
        bool reach=false;
        // agentsPositive.

        if(temp2!=0)
        {
            if(!IsOverTheLine)
            {
            switch(state)
            {
            case 0:{ //Go Behind the Object

                Vector2D space2=diff2;
                //int side = agentsPositive.at(index).goalRegion;
                space2.setLength(300);
                //space2.setDir(space2.dir() + M_PI*side);
                rc.maxSpeed=0.8;
                rc.useNav = true;
                rc.fin_pos.loc=point2  - space2;
                rc.fin_pos.dir=diff2.dir().radian();
                reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
                if(reach) state = 1;

            }
                break;
            case 1:{//Ready to Push

                rc.useNav = false;
                rc.maxSpeed=0.4;
                int side = -1;//agentsPositive.at(index).goalRegion;
                rc.fin_pos.loc.x=point2.x +(side)*100*(diff2.x)/(diff2.length());
                rc.fin_pos.loc.y=point2.y +(side)*100*(diff2.y)/(diff2.length());
                rc.fin_pos.dir=diff2.dir().radian();
                if(((wm->ourRobot[id].pos.loc-point2).length())>400) state=0;
                reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
                if(reach)
                    state = 2;
            }
                break;
            case 2:{//Push
                //Vector2D diff2 = region2.center() - wm->ourRobot[id].pos.loc ;
                rc.useNav = false;
                if(diff2.length() > 1500) diff2.setLength(1500);
                if(((wm->ourRobot[id].pos.loc-point2).length())>300) state=0;
                if(((wm->ourRobot[id].pos.loc-point2).length())<180) state=0;
                rc.fin_pos.loc=point2 + diff2/5;
                rc.fin_pos.dir=diff2.dir().radian();
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
            }
                break;
            case 3:{//Release

                // if(testseg->existIntersection(*o2o))
                //{
                qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
                count++;
                //if(index==agentsR1.size()) rc.fin_pos.loc=Vector2D(0,0);
                if(temp2==0)
                {
                    rc.fin_pos.loc=origin2;//Vector2D(1500,1500);
                    break;
                }
                //agentsR1.takeFirst();
                //index++;
                // }
                //if(reach)
                state = 0;
            }
                break;
            }
        }
            else
            {
                {
                switch(state)
                {
                case 0:{ //Go Behind the Object

                    Vector2D space2=diff2;
                    //int side = agentsPositive.at(index).goalRegion;
                    space2.setLength(300);
                    //space2.setDir(space2.dir() + M_PI*side);
                    rc.maxSpeed=0.8;
                    rc.useNav = true;
                    rc.fin_pos.loc=point2 ;// - space2;
                    rc.fin_pos.loc.x-=300;
                    rc.fin_pos.dir=0;//diff2.dir().radian();
                    reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
                    if(reach) state = 1;

                }
                    break;
                case 1:{//Ready to Push

                    rc.useNav = false;
                    rc.maxSpeed=0.4;
                    int side = -1;//agentsPositive.at(index).goalRegion;
                    rc.fin_pos.loc.x=point2.x +(side)*100;//*(diff2.x)/(diff2.length());
                    rc.fin_pos.loc.y=point2.y;// +(side)*100*(diff2.y)/(diff2.length());
                    rc.fin_pos.dir=0;//diff2.dir().radian();
                    if(((wm->ourRobot[id].pos.loc-point2).length())>400) state=0;
                    reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
                    if(reach)
                        state = 2;
                }
                    break;
                case 2:{//Push
                    //Vector2D diff2 = region2.center() - wm->ourRobot[id].pos.loc ;
                    rc.useNav = false;
                    double delta=(wm->ourRobot[id].pos.loc.x-origin.x)/5;
                    if(delta > 1500) delta=1500;
                    if(((wm->ourRobot[id].pos.loc-point2).length())>300) state=0;
                    if(((wm->ourRobot[id].pos.loc-point2).length())<180) state=0;
                    rc.fin_pos.loc=point2;
                    rc.fin_pos.loc.x -= delta;
                    rc.fin_pos.dir=0;//diff2.dir().radian();

                }
                    break;
            }
            }
            }
        }

//----------------------------------------------------------------------------

    }
    qDebug()<< "fin_pos.x  " << rc.fin_pos.loc.x << "  Y  "<<rc.fin_pos.loc.y<< " ------------------------------ STATE = " << state ;


    rc.maxSpeed = 1.2;
    rc.isBallObs = false;
    rc.isKickObs = true;
    return rc;
}
// ==================================================================================
void TacticConfront::addData()
{

    agentsNegative.clear();
    agentsNegative.insert(0,wm->ball.pos.loc);//wm->ourRobot[0].pos.loc);
    agentsNegative.insert(1,wm->ourRobot[1].pos.loc);
    agentsNegative.insert(2,wm->ourRobot[2].pos.loc);

    agentsPositive.clear();
    agentsPositive.insert(0,wm->ourRobot[4].pos.loc);//wm->ourRobot[0].pos.loc);
    agentsPositive.insert(1,wm->ourRobot[5].pos.loc);

    agentsPositive.insert(2,wm->oppRobot[0].pos.loc);
}
// ==================================================================================
void TacticConfront::addseg()
{

    segList.clear(); // SO IMPORTANT !!!
    tseg = new Segment2D(Vector2D(-500, 2000),Vector2D(0,0));
    segList.insert(0,*tseg);
    tseg = new Segment2D(Vector2D(-500,-2000),Vector2D(0,0));
    segList.insert(1,*tseg);


}
// ==================================================================================
Vector2D TacticConfront::findnearest(Vector2D input)
{
    //int tmp = 0 ;
    double dist;
    Vector2D point=Vector2D(1000000,1000000);//,point2;
    for(int k=0;k<segList.size();k++)
    {
        dist=(input-point).length2();
        if((input-segList.at(k).nearestPoint(input)).length2()<dist) point=segList.at(k).nearestPoint(input);

    }
    return point;
}

//void TacticConfront::mergeData()
//{
//    mergedList.clear();
//    for(int i=0;i<agentsR0.size();i++)
//    {
//        AgentsAndRegions temp;
//        temp.pos=agentsR0.at(i);
//        temp.goalRegion=0;
//        mergedList.insert(i,temp);
//    }

//    for(int i=0;i<agentsR1.size();i++)
//    {
//        AgentsAndRegions temp;
//        temp.pos=agentsR1.at(i);
//        temp.goalRegion=1;
//        mergedList.insert(i+agentsR0.size(),temp);
//    }
//}
// ==================================================================================
void TacticConfront::sortData()
{
    for(int i=0;i<agentsPositive.size();i++)
    {
        //for(int j=0;j<segList.size();j++)
        //{
        for(int k=i+1;k<agentsPositive.size();k++)
        {
            if( (agentsPositive.at(i)-findnearest(agentsPositive.at(i))).length2()
                    > (agentsPositive.at(k)-findnearest(agentsPositive.at(k))).length2() ) agentsPositive.swap(i,k);
        }
        //}

    }

    for(int i=0;i<agentsNegative.size();i++)
    {
        //for(int j=0;j<segList.size();j++)
        //{
        for(int k=i+1;k<agentsNegative.size();k++)
        {
            if( (agentsNegative.at(i)-findnearest(agentsNegative.at(i))).length2()
                    > (agentsNegative.at(k)-findnearest(agentsNegative.at(k))).length2() ) agentsNegative.swap(i,k);
        }
        //}

    }
}
// ==================================================================================
// ==================================================================================
