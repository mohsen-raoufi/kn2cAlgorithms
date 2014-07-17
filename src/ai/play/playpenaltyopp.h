#ifndef PLAYPENALTYOPP_H
#define PLAYPENALTYOPP_H

#include "play.h"

class PlayPenaltyOpp : public Play
{
    Q_OBJECT
public:
    explicit PlayPenaltyOpp(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    //virtual Tactic* getTactic(int id);
    virtual int enterCondition();

private:
    TacticDefender* tDefenderMid;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticGoalie* tGoalie;
    TacticHalt* tHalt;

};

#endif // PLAYPENALTYOPP_H
