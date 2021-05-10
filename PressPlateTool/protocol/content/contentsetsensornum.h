#ifndef CONTENTSETSENSORNUM_H
#define CONTENTSETSENSORNUM_H
#include "icontent.h"

class ContentSetSensorNum : public IContent
{
public:
    explicit ContentSetSensorNum(uint8_t data);

    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;
    bool success() override {
        return isSuccess;
    }
    uint8_t sensorNum() override {
        return num;
    }
private:
    uint8_t num;
    bool isSuccess;

};

#endif // CONTENTSETSENSORNUM_H
