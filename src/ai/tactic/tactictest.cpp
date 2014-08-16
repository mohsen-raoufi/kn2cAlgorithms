#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
    count=0;
    origin=Vector2D(1500,0);
    obs=0;
}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;
    rc.fin_pos.loc=origin;



    //testline=new Line2D(Vector2D(-500,2000),Vector2D(500,-2000));
    //Line2D perp=testline->perpendicular(Vector2D(1,1));
    //double doost=testline->dist(Vector2D(1,1));
//    Vector2D proj=testline->projection(wm->ball.pos.loc);
//    qDebug() << proj.x<< "------ Y = " << proj.y ; // length();//atan(perp.a()/perp.b())*180/M_PI;
//    qDebug() << wm->ball.pos.loc.x<< "------ Y = " << wm->ball.pos.loc.y ;

    testseg = new Segment2D(Vector2D(-500,2000),Vector2D(500,-2000));//0,0));//
    //seg2 = new Segment2D(Vector2D(0,2000),Vector2D(500,-2000))

    addData();
    mergeData();
    sortData();


    //Line2D segline = testseg->line();
    //double y=segline.getX(500);
    //qDebug() << y;

//    Vector2D proj=testseg->nearestPoint(wm->ball.pos.loc);
//    qDebug() << proj.x<< "------ Y = " << proj.y ; // length();//atan(perp.a()/perp.b())*180/M_PI;
//    qDebug() << wm->ball.pos.loc.x<< "------ Y = " << wm->ball.pos.loc.y ;
//    testseg->existIntersection();





    for(int i=0;i<mergedList.size();i++)
    {
        //if(obstacle)wm->kn->)
        //{continue; }
        r2o = new Segment2D(Vector2D(wm->ourRobot[id].pos.loc) , Vector2D(mergedList.at(i).pos));
        o2o = new Segment2D(origin , Vector2D(mergedList.at(i).pos));
        temp=0;
        if(!testseg->existIntersection(*o2o))
                //!region[mergedList.at(i).goalRegion].IsInside(mergedList.at(i).pos))
        {
            qDebug() << mergedList.at(i).pos.x << " Y ---- " << mergedList.at(i).pos.y;// TOOOOOOOOOOOOOOOOOOOSHE !!!!!!!" << index ;
            index=i;
            //goalRegion=mergedList.at(i).goalRegion;
            temp=1;
            break;
        }
    }


    Vector2D point2 = mergedList.at(index).pos;//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D diff2 = testseg->nearestPoint(point2) - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    // mergedList.

    if(temp!=0)
    {
    switch(state)
    {
    case 0:{ //Go Behind the Object

        Vector2D space2=diff2;
        space2.setLength(300);
        rc.maxSpeed=0.8;
        rc.useNav = true;
        rc.fin_pos.loc=point2 - space2;
        rc.fin_pos.dir=diff2.dir().radian();
        reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
        if(reach) state = 1;

    }
        break;
    case 1:{//Ready to Push

        rc.useNav = false;
        rc.maxSpeed=0.4;
        rc.fin_pos.loc.x=point2.x - 100*(diff2.x)/(diff2.length());
        rc.fin_pos.loc.y=point2.y - 100*(diff2.y)/(diff2.length());
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
        reach=testseg->existIntersection(*o2o);//wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,200);
        if(reach)
        {
        state = 3;
        qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
        count++;
        if(temp==0)
        {
            rc.fin_pos.loc=origin;//Vector2D(1500,1500);
            break;
        }
        }
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

    qDebug()<< "----------------------------------------" << count << "------- STATE = " << state ;

    rc.maxSpeed = 1.2;
    rc.isBallObs = false;
    rc.isKickObs = true;
    return rc;
}

void TacticTest::addData()
{
    agentsR1.clear();
    agentsR1.insert(0,wm->ball.pos.loc);//wm->ourRobot[0].pos.loc);
    agentsR1.insert(1,wm->ourRobot[1].pos.loc);
    agentsR1.insert(2,wm->ourRobot[2].pos.loc);

    agentsR0.clear();
    agentsR0.insert(0,wm->ourRobot[4].pos.loc);//wm->ourRobot[0].pos.loc);
    agentsR0.insert(1,wm->ourRobot[5].pos.loc);

    agentsR0.insert(2,wm->oppRobot[0].pos.loc);
}

void TacticTest::mergeData()
{
    mergedList.clear();
    for(int i=0;i<agentsR0.size();i++)
    {
        AgentsAndRegions temp;
        temp.pos=agentsR0.at(i);
        temp.goalRegion=0;
        mergedList.insert(i,temp);
    }

    for(int i=0;i<agentsR1.size();i++)
    {
        AgentsAndRegions temp;
        temp.pos=agentsR1.at(i);
        temp.goalRegion=1;
        mergedList.insert(i+agentsR0.size(),temp);
    }
}

void TacticTest::sortData()
{
    for(int i=0;i<mergedList.size();i++)
    {
        for(int k=i+1;k<mergedList.size();k++)
        {
            if( (mergedList.at(i).pos-testseg->nearestPoint(mergedList.at(i).pos)).length2()
              > (mergedList.at(k).pos-testseg->nearestPoint(mergedList.at(k).pos)).length2() ) mergedList.swap(i,k);
        }

    }
}
