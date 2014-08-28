#include "playtest.h"

PlayTest::PlayTest(WorldModel *worldmodel, QObject *parent) :
    Play("PlayTest", worldmodel, parent)
{
    //tTest=new TacticConfront(wm);
    tTest=new TacticPush2Goal(wm);
    //tTest=new TacticAttacker(wm);
    //tTest=new TacticTest(wm);
    //tTest=new TacticTransferObject(wm);
}

int PlayTest::enterCondition()
{
    return 1000000000;
}

void PlayTest::execute()
{

    tactics[3]=tTest;
    return ;

}

