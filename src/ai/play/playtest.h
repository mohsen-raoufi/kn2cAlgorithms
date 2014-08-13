#ifndef PLAYTEST_H
#define PLAYTEST_H

#include "play.h"

class PlayTest : public Play
{
    Q_OBJECT
public:
    explicit PlayTest(WorldModel *worldmodel, QObject *parent = 0);
    virtual void execute();
    virtual int enterCondition();

private:
    QList<Position> region1;
    QList<Position> region2;

    Rect2D rect1;
    Rect2D rect2;

    TacticTest *tTest;

};

#endif // PLAYTEST_H
