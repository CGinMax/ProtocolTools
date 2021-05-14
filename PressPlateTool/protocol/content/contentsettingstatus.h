#ifndef CONTENTSETTINGSTATUS_H
#define CONTENTSETTINGSTATUS_H

#include "icontent.h"

class ContentSettingStatus : public IContent
{
public:
    explicit ContentSettingStatus(uint8_t data);
    std::string toString(bool isSend) override;
    std::vector<uint8_t> toByteVector() override;

    uint8_t setStatusCode() override {
        return m_status;
    }
    bool success() override {
        return m_isSuccess;
    }

private:
    uint8_t m_status;
    bool m_isSuccess;
};

#endif // CONTENTSETTINGSTATUS_H
