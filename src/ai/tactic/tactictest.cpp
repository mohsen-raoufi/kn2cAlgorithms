#include "tactictest.h"


TacticTest::TacticTest(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTest", worldmodel, parent)
{
//    agentsForFirstRegion.push_back(wm->oppRobot[0].pos.loc);
//    agentsForFirstRegion.append(wm->oppRobot[1].pos.loc);
//    agentsForFirstRegion.append(wm->oppRobot[2].pos.loc);

//    agentsForSecondRegion.insert(0,wm->ourRobot[0].pos.loc);
//    agentsForSecondRegion.insert(1,wm->oppRobot[4].pos.loc);
//    agentsForSecondRegion.insert(2,wm->oppRobot[5].pos.loc);
    region1.assign(Vector2D(-1000,1500),Size2D(1000,500));
    region2.assign(Vector2D(-1000,-2000),Size2D(1000,500));
    state=0;
    index=0;
    firstInit=false;
}

RobotCommand TacticTest::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 1.2;

    addData();
    for(int i=0;i<agentsForSecondRegion.size();i++)
    {
        temp=0;
        if(!region2.IsInside(agentsForSecondRegion.at(i)))
        {
            index=i;
            temp++;
            break;
        }

    }



    //Vector2D point2 = region1.bottomRight();
    //Vector2D point3 =wm->ball.pos.loc;
    //qDebug()<<"count:"<<agentsForSecondRegion.count();
    //bool inside = region2.IsInside(wm->ball.pos.loc);
    //qDebug() << "topleft:" << point.x << " ------- y : " << point.y << inside;//
    //qDebug() << "topright:" << point2.x << " ------- y : " << point2.y;
    //qDebug() << "ball:" << point3.x << " ------- y : " << point3.y;
    //agentsForSecondRegion.clear();


    Vector2D point2 = agentsForSecondRegion.at(index);//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsForFirstRegion.first().loc;
    Vector2D diff2 = region2.center() - point2;// wm->ourRobot[id].pos.loc ;
    bool reach=false;
    if(temp!=0)
    {
    switch(state)
    {
    case 0:{ //Go Behind the Object

        Vector2D space2=diff2;
        space2.setLength(300);
        rc.maxSpeed=1.5;
        rc.useNav = true;
        rc.fin_pos.loc=point2 - space2;
        rc.fin_pos.dir=diff2.dir().radian();
        reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,50);
        if(reach) state = 1;

    }
        break;
    case 1:{//Ready to Push
        rc.useNav = false;
        rc.maxSpeed=0.7;
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
        rc.fin_pos.loc=point2 + diff2/5;
        rc.fin_pos.dir=diff2.dir().radian();
        reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,150);
        if(reach)
        state = 3;
    }
        break;
    case 3:{//Release
        if(region2.IsInside(point2))
        {
            qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
            //if(index==agentsForSecondRegion.size()) rc.fin_pos.loc=Vector2D(0,0);
            if(temp==0)
            {
                rc.fin_pos.loc=Vector2D(0,0);
                break;
            }
            //agentsForSecondRegion.takeFirst();
            //index++;
        }
        //if(reach)
        state = 0;
    }
        break;
    }
    }

    qDebug() << rc.fin_pos.loc.x << " -------  Y = " << rc.fin_pos.loc.y << " STATE = " << state;



    //rc.useNav = false;
    rc.isBallObs = false;
    rc.isKickObs = true;
        return rc;
}

void TacticTest::addData()
{
    agentsForSecondRegion.clear();
    agentsForSecondRegion.insert(0,wm->ball.pos.loc);//wm->ourRobot[0].pos.loc);
    agentsForSecondRegion.insert(1,wm->ourRobot[1].pos.loc);
    agentsForSecondRegion.insert(2,wm->ourRobot[2].pos.loc);
}
