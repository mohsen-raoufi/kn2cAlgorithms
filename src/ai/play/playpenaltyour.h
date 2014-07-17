#ifndef PLAYPENALTYOUR_H
#define PLAYPENALTYOUR_H

#include "play.h"

class PlayPenaltyOur : public Play
{
    Q_OBJECT
public:
    explicit PlayPenaltyOur(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition();

private:
    int numberOfDef;
    TacticPenaltyKicker* penaltyKicker;
    TacticDefender* tDefenderMid;
    TacticDefender* tDefenderLeft;
    TacticDefender* tDefenderRight;
    TacticGoalie* tGoalie;
    TacticHalt* tHalt;

};

#endif // PLAYPENALTYOUR_H
