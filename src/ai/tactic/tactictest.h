#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"
#include "tactictransferobject.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();
    void mergeData();
    void sortData();
    Vector2D findnearest(Vector2D input);

private:
    QList<Vector2D> balls;//R0;
    //QList<Vector2D> a4fSorted;
    //QList<Vector2D> agentsNegative;//R1;
    //QList<AgentsAndRegions> mergedList;
    //QList<Segment2D> segList;
    //QList<Vector2D> a4sSorted;
    //Rect2D region[2];
    //Rect2D region2;
    bool firstInit;
    bool IsInside,IsInside2,unAccessible;
    int state,state2;
    int index;
    //int obs;
    //int goalRegion;
    int temp,temp2;
    int count;
    Circle2D circularBorder,circularBorderOut,hole1,hole2;
    //Line2D *testline;
    //Segment2D *testseg;
    //Segment2D *tseg;
    Segment2D *r2o; // Robot to Object
    Segment2D *c2o; // cCenter to Object
    //Segment2D *seg[2]; // 2 segment line
    Vector2D vec2goal;//origin,origin2;
};

#endif // TACTICTEST_H
