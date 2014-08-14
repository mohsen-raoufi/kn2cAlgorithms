#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"
struct allAgents
{
    Vector2D pos;
    int goalRegion;
};

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();
    void mergeData();

private:
    QList<Vector2D> agentsR1;
    //QList<Vector2D> a4fSorted;
    QList<Vector2D> agentsR2;
    QList<allAgents> mergedList;
    //QList<Vector2D> a4sSorted;
    Rect2D region1;
    Rect2D region2;
    bool firstInit;
    int state;
    int index;
    int temp;
};

#endif // TACTICTEST_H
