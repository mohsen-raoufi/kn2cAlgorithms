#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    //region1.append();
}

int PlayTest::enterCondition()
{
    return 0;
}

void PlayTest::execute()
{

    return ;

}

