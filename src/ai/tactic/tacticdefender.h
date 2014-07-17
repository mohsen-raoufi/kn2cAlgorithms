#ifndef TACTICDEFENDER_H
#define TACTICDEFENDER_H

#include "tactic.h"

class TacticDefender : public Tactic
{
    Q_OBJECT
public:
    explicit TacticDefender(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void setDefenderPos(int pos);
private:
    Vector2D GotoDefaultLoc(int total, int current);
    int numberOfDefenders;
    int position;
};

#endif // TACTICDEFENDER_H
