#ifndef CONTENTQUERYADDR_H
#define CONTENTQUERYADDR_H

#include "icontent.h"

class ContentQueryAddr : public IContent
{
public:
    explicit ContentQueryAddr(uint8_t low = 0x00, uint8_t high = 0x00);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

    uint16_t testAddress() override {
        return addr;
    }
private:
    uint16_t addr;
};

#endif // CONTENTQUERYADDR_H
