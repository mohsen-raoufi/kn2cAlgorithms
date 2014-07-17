#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    penaltyKicker=new TacticAttacker(wm);
    tDefenderMid=new TacticDefender(wm);
    tDefenderLeft=new TacticDefender(wm);
    tDefenderRight=new TacticDefender(wm);
    tHalt=new TacticHalt(wm);
}

int PlayTest::enterCondition()
{
    return 0;
}

void PlayTest::execute()
{

    return ;

}

