#ifndef CONTENTNAKERROR_H
#define CONTENTNAKERROR_H

#include "icontent.h"
class ContentNAKError : public IContent
{
public:
    explicit ContentNAKError(uint8_t errorFunctionCode, uint8_t errorNakCode);

    std::string toString(bool isSend) override;

    std::vector<uint8_t> toByteVector() override;

    uint8_t errorFunCode() override {
        return errFunCode;
    }
    uint8_t nakCode() override {
        return nakFunCode;
    }

private:
    uint8_t errFunCode;
    uint8_t nakFunCode;
};

#endif // CONTENTNAKERROR_H
