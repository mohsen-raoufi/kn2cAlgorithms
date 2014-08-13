#include "playpenaltyour.h"

PlayPenaltyOur::PlayPenaltyOur(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOur", worldmodel, parent)
{
    numberOfDef=NUMOFDEFENDERS;

    tGoalie=new TacticGoalie(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tHalt=new TacticHalt(wm);
    penaltyKicker=new TacticPenaltyKicker(wm);

    tDefenderMid->setDefenderPos(CENTER);
    tDefenderLeft->setDefenderPos(LEFT);
    tDefenderRight->setDefenderPos(RIGHT);
}

int PlayPenaltyOur::enterCondition()
{
    if(wm->cmgs.ourPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOur::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);

    tactics[wm->ref_goalie_our]=tGoalie;

    switch (activeAgents.length()) {

    case 1:
        tactics[activeAgents.takeFirst()]=penaltyKicker;
        break;
    case 2:
       tactics[activeAgents.takeFirst()]=tDefenderMid;
       tactics[activeAgents.takeFirst()]=penaltyKicker;
       break;
    case 3:
        tactics[activeAgents.takeFirst()]=tDefenderLeft;
        tactics[activeAgents.takeFirst()]=tDefenderRight;
        tactics[activeAgents.takeFirst()]=penaltyKicker;
        break;
    case 4:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tHalt;
            tactics[activeAgents.takeFirst()]=penaltyKicker;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=penaltyKicker;
            break;
        }
        break;
    case 5:
        switch (numberOfDef) {
        case 2:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tHalt;
            tactics[activeAgents.takeFirst()]=tHalt;
            tactics[activeAgents.takeFirst()]=penaltyKicker;
            break;
        case 3:
            tactics[activeAgents.takeFirst()]=tDefenderRight;
            tactics[activeAgents.takeFirst()]=tDefenderLeft;
            tactics[activeAgents.takeFirst()]=tDefenderMid;
            tactics[activeAgents.takeFirst()]=tHalt;
            tactics[activeAgents.takeFirst()]=penaltyKicker;
            break;
        }
        break;
    }
}
