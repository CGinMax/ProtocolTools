#ifndef ENUMS_H
#define ENUMS_H

enum NetworkType{
    eTcpServer = 0,
    eTcpClient,
    eUdp,
    eSerialPort
};

enum eStationType{
    WF = 0, // 五防
    Minitor,// 监控
};

enum eProtocol {
    CDTStandard = 0,// 标准
    CDTGc,  // 共创
    CDTUt,  // 优特
    CDTNr,  // 南瑞
};

#endif // ENUMS_H
