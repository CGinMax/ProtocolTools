#ifndef CONTENTQUERYSTATUS_H
#define CONTENTQUERYSTATUS_H

#include "icontent.h"
#include <array>
class ContentQueryStatus : public IContent
{
public:
    explicit ContentQueryStatus(uint8_t curCode = 0x00, uint8_t setCode = 0x00);

    static std::array<std::string, 6> currentStatus;
    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

private:
    uint8_t currentCode;
    uint8_t setCode;

};

#endif // CONTENTQUERYSTATUS_H
