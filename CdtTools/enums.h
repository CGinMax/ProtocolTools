#ifndef ENUMS_H
#define ENUMS_H

enum eNetworkType{
    eTcpServer = 0,
    eTcpClient,
    eUdp,
    eSerialPort
};

enum eStationType{
    Minitor = 0,// 监控
    WF, // 五防
};

enum eProtocol {
    CDTStandard = 0,// 标准
    CDTGc,  // 共创
    CDTUt,  // 优特
    CDTNr,  // 南瑞
};

#endif // ENUMS_H
