#ifndef TACTICSTOP_H
#define TACTICSTOP_H
#define DIFF AngleDeg::PI/10

#include "tactic.h"

class TacticStop : public Tactic
{
    Q_OBJECT
public:
    explicit TacticStop(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void setStopPosition(int pos);

protected:
    int position;
};

#endif // TACTICSTOP_H
