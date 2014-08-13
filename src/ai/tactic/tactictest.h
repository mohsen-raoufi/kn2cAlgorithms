#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();

private:
    QList<Vector2D> agentsForFirstRegion;
    QList<Vector2D> agentsForSecondRegion;
};

#endif // TACTICTEST_H
