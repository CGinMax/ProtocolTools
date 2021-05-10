#ifndef CONTENTSETTINGADDR_H
#define CONTENTSETTINGADDR_H

#include "icontent.h"

class ContentSettingAddr : public IContent
{
public:
    explicit ContentSettingAddr(uint8_t dataCode);

    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;

    uint8_t setAddress() override {
        return addr;
    }

    bool success() override {
        return isSuccess;
    }

private:
    uint8_t addr;
    bool isSuccess;
};

#endif // CONTENTSETTINGADDR_H
