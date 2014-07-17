#ifndef PLAYTEST_H
#define PLAYTEST_H

#include "play.h"

class PlayTest : public Play
{
    Q_OBJECT
public:
    explicit PlayTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticAttacker* penaltyKicker;
    TacticDefender* tDefenderMid;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticHalt* tHalt;

};

#endif // PLAYTEST_H
