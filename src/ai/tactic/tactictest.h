#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();

private:
    QList<Vector2D> agentsForFirstRegion;
    QList<Vector2D> agentsForSecondRegion;
    Rect2D region1;
    Rect2D region2;
    bool firstInit;
    int state;
    int index;
    int temp;
};

#endif // TACTICTEST_H
