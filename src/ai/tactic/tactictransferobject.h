#ifndef TACTICTRANSFEROBJECT_H
#define TACTICTRANSFEROBJECT_H

#include "tactic.h"
struct AgentsAndRegions
{
    Vector2D pos;
    int goalRegion;
};

class TacticTransferObject : public Tactic
{
    Q_OBJECT
public:
    explicit TacticTransferObject(WorldModel *worldmodel, QObject *parent = 0);
    virtual RobotCommand getCommand();
    void addData();
    void mergeData();
    void sortData();

private:
    QList<Vector2D> agentsR0;
    //QList<Vector2D> a4fSorted;
    QList<Vector2D> agentsR1;
    QList<AgentsAndRegions> mergedList;
    //QList<Vector2D> a4sSorted;
    Rect2D region[2];
    //Rect2D region2;
    bool firstInit;
    int state;
    int index;
    int goalRegion;
    int temp;
};

#endif // TACTICTRANSFEROBJECT_H
