#ifndef CONTENTSETTINGADDR_H
#define CONTENTSETTINGADDR_H

#include "icontent.h"

class ContentSettingAddr : public IContent
{
public:
    explicit ContentSettingAddr(uint8_t dataCode);

    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;

private:
    uint8_t code; // addr or status
};

#endif // CONTENTSETTINGADDR_H
