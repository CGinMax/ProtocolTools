#ifndef ENUMS_H
#define ENUMS_H

enum eNetworkType{
    eErrorNetworkType = -1,
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
    CDTStandardary = 0,// 标准
    CDTGcInterace,  // 交互式共创
    CDTUt,  // 优特
    CDTNr,  // 南瑞
    NRUdp,  // 南瑞udp
};

#endif // ENUMS_H
