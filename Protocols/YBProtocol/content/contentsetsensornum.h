#ifndef CONTENTSETSENSORNUM_H
#define CONTENTSETSENSORNUM_H
#include "icontent.h"

class PROTOCOLSSHARED_EXPORT ContentSetSensorNum : public IContent
{
public:
    explicit ContentSetSensorNum(uint8_t data);

    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;
    bool success() override {
        return m_isSuccess;
    }
    uint8_t sensorNum() override {
        return m_num;
    }
private:
    uint8_t m_num;
    bool m_isSuccess;

};

#endif // CONTENTSETSENSORNUM_H
