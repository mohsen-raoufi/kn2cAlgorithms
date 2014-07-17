#ifndef TACTICPENALTYKICKER_H
#define TACTICPENALTYKICKER_H

#include "tacticattacker.h"

class TacticPenaltyKicker:public TacticAttacker
{
    Q_OBJECT
public:
    explicit TacticPenaltyKicker(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
};

#endif // TACTICPENALTYKICKER_H
