#ifndef CONTENTSETTINGADDR_H
#define CONTENTSETTINGADDR_H

#include "icontent.h"

class ContentSettingAddr : public IContent
{
public:
    ContentSettingAddr();

    std::string toString(const std::vector<uint8_t> &datas, bool isSend) override;
};

#endif // CONTENTSETTINGADDR_H
