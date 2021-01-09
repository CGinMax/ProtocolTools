#ifndef FRAME_H
#define FRAME_H
#include <QByteArray>

class Frame
{
public:
    Frame();
    virtual QByteArray toAllByteArray() {
        return QByteArray();
    }
};

#endif // FRAME_H
