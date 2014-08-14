#include "tactictransferobject.h"

TacticTransferObject::TacticTransferObject(WorldModel *worldmodel, QObject *parent) :
    Tactic("TacticTransferObject", worldmodel, parent)
{
//    agentsR0.push_back(wm->oppRobot[0].pos.loc);
//    agentsR0.append(wm->oppRobot[1].pos.loc);
//    agentsR0.append(wm->oppRobot[2].pos.loc);

//    agentsR1.insert(0,wm->ourRobot[0].pos.loc);
//    agentsR1.insert(1,wm->oppRobot[4].pos.loc);
//    agentsR1.insert(2,wm->oppRobot[5].pos.loc);
region[0].assign(Vector2D(-1000,1500),Size2D(1000,500));
region[1].assign(Vector2D(-1000,-2000),Size2D(1000,500));
state=0;
index=0;
firstInit=false;
}

RobotCommand TacticTransferObject::getCommand()
{
    RobotCommand rc;
    if(!wm->ourRobot[id].isValid) return rc;

    rc.maxSpeed = 1.2;

    addData();
    mergeData();
    sortData();

    for(int i=0;i<mergedList.size();i++)
    {
        temp=0;
        if(!region[mergedList.at(i).goalRegion].IsInside(mergedList.at(i).pos))
        {
            qDebug() << mergedList.at(i).pos.x << " Y ---- " << mergedList.at(i).pos.y;// TOOOOOOOOOOOOOOOOOOOSHE !!!!!!!" << index ;
            index=i;
            goalRegion=mergedList.at(i).goalRegion;
            temp=1;
            break;
        }

    }


    //Vector2D point2 = region1.bottomRight();
    //Vector2D point3 =wm->ball.pos.loc;
    //qDebug()<<"count:"<<agentsR1.count();
    //bool inside = region2.IsInside(wm->ball.pos.loc);
    //qDebug() << "topleft:" << point.x << " ------- y : " << point.y << inside;//
    //qDebug() << "topright:" << point2.x << " ------- y : " << point2.y;
    //qDebug() << "ball:" << point3.x << " ------- y : " << point3.y;
    //agentsR1.clear();


    Vector2D point2 = mergedList.at(index).pos;//;//temp.loc;//wm->ourRobot[id].pos.loc;//agentsR0.first().loc;
    Vector2D diff2 = region[goalRegion].center() - point2;// wm->ourRobot[id].pos.loc ;
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
        if(((wm->ourRobot[id].pos.loc-point2).length())>400) state=0;
        rc.fin_pos.loc=point2 + diff2/5;
        rc.fin_pos.dir=diff2.dir().radian();
        reach=wm->kn->ReachedToPos(wm->ourRobot[id].pos.loc,rc.fin_pos.loc,150);
        if(reach)
        state = 3;
    }
        break;
    case 3:{//Release

        if(region[goalRegion].IsInside(point2))
        {
            qDebug() << " INNNNNNNNNNNN SIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDE !!!";
            //if(index==agentsR1.size()) rc.fin_pos.loc=Vector2D(0,0);
            if(temp==0)
            {
                rc.fin_pos.loc=Vector2D(0,0);
                break;
            }
            //agentsR1.takeFirst();
            //index++;
        }
        //if(reach)
        state = 0;
    }
        break;
    }
    }

//    for(int i=0;i<mergedList.size();i++)
//    {
//        Vector2D point3=mergedList.at(i).pos;
//        qDebug() << point3.x << " ----- Y= " << point3.y << "    STATE = " << state << " REGION = " << mergedList.at(i).goalRegion ;
//    }
//
    //Vector2D point3=region[mergedList.at(index).goalRegion].center();
    //qDebug() << point3.x << " ----- Y= " << point3.y;
    //qDebug() << rc.fin_pos.loc.x << " -------  Y = " << rc.fin_pos.loc.y << " STATE = " << state;
    qDebug() << "STATE = " << state;

    //rc.fin_pos.loc=Vector2D(0,0);
    //rc.useNav = false;
    rc.isBallObs = false;
    rc.isKickObs = true;
    return rc;
}

void TacticTransferObject::addData()
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

void TacticTransferObject::mergeData()
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

void TacticTransferObject::sortData()
{
    for(int i=0;i<mergedList.size();i++)
    {
        for(int k=i+1;k<mergedList.size();k++)
        {
            if( (mergedList.at(i).pos-region[mergedList.at(i).goalRegion].center()).length2()
              > (mergedList.at(k).pos-region[mergedList.at(k).goalRegion].center()).length2() ) mergedList.swap(i,k);
        }

    }
}
