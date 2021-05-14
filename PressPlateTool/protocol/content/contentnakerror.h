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
        return m_errFunCode;
    }
    uint8_t nakCode() override {
        return m_nakFunCode;
    }

private:
    uint8_t m_errFunCode;
    uint8_t m_nakFunCode;
};

#endif // CONTENTNAKERROR_H
