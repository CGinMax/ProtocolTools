#ifndef CONTENTSETTINGSTATUS_H
#define CONTENTSETTINGSTATUS_H

#include "icontent.h"

class ContentSettingStatus : public IContent
{
public:
    ContentSettingStatus();
    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTSETTINGSTATUS_H
