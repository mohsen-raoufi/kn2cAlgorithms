#ifndef TACTICPUSH2GOAL_H
#define TACTICPUSH2GOAL_H

#include "tactic.h"

class TacticPush2Goal: public Tactic
{
    Q_OBJECT
public:
    explicit TacticPush2Goal(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();
    void sortData();
    Vector2D GoOncircle(Vector2D center,double radius);//,Vector2D Object);
    Vector2D AvoidtoEnterCircle(Circle2D Ci , Vector2D pnt, Vector2D finPOS);
private:
    QList<Vector2D> balls;
    bool firstInit;
    bool IsInside,unAccessible;
    bool DontEnterCircle;
    int state,state2;
    int index;
    int temp,temp2;
    int count;
    Circle2D circularBorder,circularBorderOut,circularBorderDANGER,circularBorder2,hole1,hole2;
    Segment2D *c2o; // cCenter to Object
    Vector2D vec2goal,diff2;//origin,origin2;
};


#endif // TACTICPUSH2GOAL_H
