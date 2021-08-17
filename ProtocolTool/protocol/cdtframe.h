#ifndef CDTFRAME_H
#define CDTFRAME_H

#include <QList>

// "字"的长度：6个字节
#define FIELD_LENGTH 6

enum eCDTParseState {
    FrameHeader,    // 同步头
    FrameControl,   // 控制字
    FrameInfo,      // 信息字
    ParseFinish,    // 解析完成
};

enum eCDTParseResult {
    HeaderError,    // 同步头错误
    ControlCrcError,// 控制字CRC校验错误
    InfoCrcError,   // 信息字CRC校验错误
    PartOfFrame,    // 未满一帧
    CompleteFrame,  // 完整帧
};

enum eCDTFrameControlType {
    StandardType = 0x71,
    ExternType = 0xF1,
    ResetType = 0x31,
    CallChildType = ResetType,
    BroadcastType = 0x21,
};

enum eCDTFrameType{
    // 上行
    RmtMeasurement = 0x61,      // 重要遥测
    RmtInformation = 0xF4,      // 遥信
    ACCType = 0x85,             // 电度

    RmtControlType = 0x57, // 遥控
    RmtControlTypeCycle = 0xF1, // 循环式遥控
};

enum eCDTFunCode{
    RmtMeasurementCode = 0x7F,      // 遥测
    RmtInformationCode = 0xF0,      // 遥信
    ACCStartCode = 0xA0,            // 电度量起始功能码
    RmtControlSelectCode = 0xE0,    // 遥控选择功能码
    RmtControlBackCode = 0xE1,     // 遥控返校
    RmtControlExecuteCode = 0xE2,   // 遥控执行
    RmtControlCancelCode = 0xE3,    // 遥控撤销
};

enum eControlLockCode{
    OpenValidLock = 0x33,       // 分解锁
    CloseValidLock = 0xCC,      // 合解锁
    ControlExecute = 0xAA,      // 执行
    ControlCancel = 0x55,       // 撤销
    ControlError = 0xFF,        // 错误
};

enum eCDTExFrameType {
    VirtualRmtInfoType = 0xA8,  // 虚遥信
    ReqRmtCtrlLockType = 0x57,  // 遥控闭锁请求
    RspRmtCtrlLockType = 0xD9,  // 遥控闭锁应答
    ChildTimingType = 0x7A,     // 子站校时
    OperTicketType = 0xB9,      // 遥控开票
};

// 信息字数据结构
struct InfoFieldEntity
{
    explicit InfoFieldEntity();
    InfoFieldEntity(uint8_t code, uint8_t data[]);
    uint8_t funCode;     // 功能码
    uint8_t dataArray[4];// 信息、数据
    uint8_t crcCode;     // CRC码

    void fillData(uint8_t funCode, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
    void calcCrc();
    QByteArray toBytes();
};

// 控制字数据结构
struct ControlEntity
{
    ControlEntity();
    uint8_t control;   // 控制字节
    uint8_t type;      // 帧类别
    uint8_t dataNum;   // 信息字数
    uint8_t sourceAddr;// 源地址
    uint8_t destAddr;  // 目的地址
    uint8_t crcCode;   // CRC码

    void fillData(uint8_t control, uint8_t type, uint8_t dataNum, uint8_t sourceAddr, uint8_t destAddr);
    void calcCrc();
    QByteArray toBytes();
};

class CDTFrame{
public:
    CDTFrame();
    ~CDTFrame() = default;
    CDTFrame(const CDTFrame &other) = default;
    CDTFrame& operator=(const CDTFrame &other) = default;

    static uint8_t header[7];
    ControlEntity frameControl;
    QList<InfoFieldEntity> infoFields; // 信息字集合

    QByteArray toByteArray();
    QByteArray toAllByteArray() const;
    eCDTParseResult parseBytesToFrame(QByteArray& data, int &index, QString& errorMsg);
    static CDTFrame createYKFrame(uint8_t ctrlCode, uint8_t type, uint8_t funCode, uint8_t operCode, uint8_t ptId);
};


#endif // CDTFRAME_H
