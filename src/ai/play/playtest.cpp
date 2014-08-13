#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    tTest=new TacticTest(wm);
}

int PlayTest::enterCondition()
{
    return 1000000;
}

void PlayTest::execute()
{
    tactics[1]=tTest;
    return ;

}

