#ifndef OUTPUTBUFFER_H
#define OUTPUTBUFFER_H

#include <QObject>
#include "wpacket.h"
#include "grpacket.h"

class OutputBuffer
{

public:
    WPacket wpck;
    grPacket grpck;

    void Clear()
    {
        wpck.Clear();
        grpck.Clear();
    }
};

#endif // OUTPUTBUFFER_H
