#ifndef CONTENTFORCESETADDR_H
#define CONTENTFORCESETADDR_H
#include "icontent.h"

class ContentForceSetAddr : public IContent
{
public:
    explicit ContentForceSetAddr(uint8_t low = 0x00, uint8_t high = 0x00);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;
private:
    uint16_t addr;
};

#endif // CONTENTFORCESETADDR_H
