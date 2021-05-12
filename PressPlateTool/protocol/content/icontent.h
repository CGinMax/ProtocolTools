#ifndef ICONTENT_H
#define ICONTENT_H

#include <string>
#include <cstdint>
#include <vector>

class IContent
{
public:
    virtual ~IContent();

    virtual std::string toString(bool isSend) = 0;
    virtual std::vector<uint8_t> toByteVector() = 0;
    virtual uint8_t functionCode() {
        return funCode;
    }
    virtual uint8_t errorFunCode() {
        return 0;
    }
    virtual uint8_t nakCode() {
        return 0;
    }
    virtual uint8_t setStatusCode() {
        return 0;
    }
    virtual bool success() {
        return false;
    }

    virtual uint8_t currentStatusCode() {
        return 0;
    }

    virtual uint8_t configedStatusCode() {
        return 0;
    }

    virtual uint8_t setAddress() {
        return 0;
    }

    virtual uint16_t testAddress() {
        return 0;
    }

    virtual uint8_t sensorNum() {
        return 0;
    }

    virtual std::string hardwareVersion() {
        return std::string();
    }
    virtual std::string softwareVersion() {
        return std::string();
    }
    virtual std::string productDescript() {
        return std::string();
    }

protected:
    uint8_t funCode;
};

#endif // ICONTENT_H