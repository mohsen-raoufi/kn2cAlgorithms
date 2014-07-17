#include "playstop.h"

PlayStop::PlayStop(WorldModel *worldmodel, QObject *parent) :
    Play("PlayStop", worldmodel, parent)
{
    numberOfDef=NUMOFDEFENDERS;

    tGolie=new TacticGoalie(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tStopMid=new TacticStop(wm);
    tStopLeft=new TacticStop(wm);
    tStopRight=new TacticStop(wm);

    tDefenderMid->setDefenderPos(CENTER);
    tDefenderLeft->setDefenderPos(LEFT);
    tDefenderRight->setDefenderPos(RIGHT);

    tStopMid->setStopPosition(CENTER);
    tStopLeft->setStopPosition(LEFT);
    tStopRight->setStopPosition(RIGHT);
}

int PlayStop::enterCondition()
{
    if(wm->gs == STATE_Stop)
        return 100;
    else if(wm->cmgs.canMove() && wm->cmgs.gameOn()==false && wm->cmgs.allowedNearBall()==false)
        return 10;
    else
        return 0;
}

void PlayStop::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);

    tactics[wm->ref_goalie_our]=tGolie;

    switch (activeAgents.length()) {

    case 1:
        tactics[activeAgents.takeFirst()]=tDefenderMid;
        break;
    case 2:
       tactics[activeAgents.takeFirst()]=tDefenderRight;
       tactics[activeAgents.takeFirst()]=tDefenderLeft;
        break;
    case 3:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tStopMid;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            break;
        }
        break;
    case 4:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tStopLeft;
            tactics[activeAgents.takeFirst()]=tStopRight;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tStopMid;
            break;
        }
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tStopLeft;
            tactics[activeAgents.takeFirst()]=tStopRight;
            tactics[activeAgents.takeFirst()]=tStopMid;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tStopLeft;
            tactics[activeAgents.takeFirst()]=tStopRight;
            break;
        }
        break;
    }

}
