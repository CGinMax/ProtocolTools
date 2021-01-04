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

#endif // ENUMS_H
