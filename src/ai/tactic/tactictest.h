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
    QList<Vector2D> agentsR0;
    //QList<Vector2D> a4fSorted;
    QList<Vector2D> agentsR1;
//    QList<AgentsAndRegions> mergedList;
    //QList<Vector2D> a4sSorted;
    Rect2D region[2];
    //Rect2D region2;
    bool firstInit;
    int state;
    int index;
    int goalRegion;
    int temp;
};

#endif // TACTICTEST_H
