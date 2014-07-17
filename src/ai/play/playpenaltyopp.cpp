#include "playpenaltyopp.h"

PlayPenaltyOpp::PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent) :
    Play("PlayPenaltyOpp", worldmodel, parent)
{
    tGoalie=new TacticGoalie(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tHalt=new TacticHalt(wm);

    tDefenderMid->setDefenderPos(CENTER);
    tDefenderLeft->setDefenderPos(LEFT);
    tDefenderRight->setDefenderPos(RIGHT);
}

int PlayPenaltyOpp::enterCondition()
{
    if(wm->cmgs.theirPenaltyKick())
        return 100;
    else
        return 0;
}

void PlayPenaltyOpp::execute()
{
    QList<int> activeAgents=wm->kn->ActiveAgents();
    activeAgents.removeOne(wm->ref_goalie_our);

    tactics[wm->ref_goalie_our]=tGoalie;

    switch (activeAgents.length()) {

    case 1:
        tactics[activeAgents.takeFirst()]=tDefenderMid;
        break;
    case 2:
       tactics[activeAgents.takeFirst()]=tDefenderRight;
       tactics[activeAgents.takeFirst()]=tDefenderLeft;
        break;
    case 3:
        tactics[activeAgents.takeFirst()]=tDefenderRight;
        tactics[activeAgents.takeFirst()]=tDefenderMid;
        tactics[activeAgents.takeFirst()]=tDefenderLeft;
        break;
    case 4:
        tactics[activeAgents.takeFirst()]=tDefenderRight;
        tactics[activeAgents.takeFirst()]=tDefenderMid;
        tactics[activeAgents.takeFirst()]=tDefenderLeft;
        tactics[activeAgents.takeFirst()]=tHalt;
        break;
    case 5:
        tactics[activeAgents.takeFirst()]=tDefenderRight;
        tactics[activeAgents.takeFirst()]=tDefenderMid;
        tactics[activeAgents.takeFirst()]=tDefenderLeft;
        tactics[activeAgents.takeFirst()]=tHalt;
        tactics[activeAgents.takeFirst()]=tHalt;
        break;
    }

}
