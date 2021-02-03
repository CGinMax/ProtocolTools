#ifndef NRUDPFRAME_H
#define NRUDPFRAME_H

#include <QObject>

namespace NrUdp {

enum eCmdType {
    Yx = 1,
    RequestYk = 2,
    AllowYk = 3,
    ForbidYk = 4,
    Yc = 5,
    VirtualYx = 5,
    DeviceStatus = 6,
};
}  // namespace NrUdp

class NrUdpFrame
{
public:
    NrUdpFrame();
    enum eNrParseResult {
        HeaderError,    // 同步头错误
        CRCError,       // crc校验错误
        PartOfFrame,    // 未满一帧
        CompleteFrame,  // 完整帧
    };


    static uint8_t header[7];
    uint16_t length;
    uint8_t srcAddr;
    uint8_t dstAddr;
    uint8_t scheduling;
    uint8_t cmdCode;
    uint8_t crcCode;

    QByteArray infoData;
    QByteArray allFrameBytes;

    eNrParseResult parseBytesToFrame(QByteArray &data, int &index, QString &errorMsg);
    void setDataBuf();
};

#endif // NRUDPFRAME_H
