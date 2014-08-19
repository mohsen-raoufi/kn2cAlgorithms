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
    //TacticTest *tTest;
    TacticConfront *tTest;
    //TacticTransferObject *tTest;


    //Line2D *testline;

};

#endif // PLAYTEST_H
