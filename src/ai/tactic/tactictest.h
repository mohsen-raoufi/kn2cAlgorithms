#ifndef TACTICTEST_H
#define TACTICTEST_H

#include "tactic.h"
#include "ball.h"
//#include "tactictransferobject.h"

class TacticTest : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();
    void mergeData();
    void sortData();
    void goOncircle2point(Vector2D pnt);
    Vector2D findnearest2circle();
    Vector2D findnearesthole(Vector2D pnt);

private:
    QList<Ball *> balls;//R0;
    //QList<Vector2D> a4fSorted;
    //QList<Vector2D> agentsNegative;//R1;
    //QList<AgentsAndRegions> mergedList;
    //QList<Segment2D> segList;
    //QList<Vector2D> a4sSorted;
    //Rect2D region[2];
    //Rect2D region2;
    bool firstInit;
    bool IsInside,IsInside2,Accessible,oppIsInField,AllIn,AnyIn,towardH1,towardH2;
    int state,state2;
    int index;
    //int obs;
    //int goalRegion;
    int temp,temp2;
    int count;
    double Uangle1,Uangle2,Dangle1,Dangle2;
    Circle2D circularBorder,circularBorderOut,hole1,hole2,circularMid;
    Line2D *ballVel;//b2h1,*b2h2;
    //Segment2D *testseg;
    //Segment2D *tseg;
    Segment2D *r2o; // Robot to Object
    Segment2D *c2o; // cCenter to Object
    //Ray2D c2b;
    //Segment2D *seg[2]; // 2 segment line
    Vector2D vec2goal,OppositeRobot,point,p2o;//,c2o,origin,origin2;
};

#endif // TACTICTEST_H
