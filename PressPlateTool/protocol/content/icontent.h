#ifndef ICONTENT_H
#define ICONTENT_H

#include <string>
#include <cstdint>
#include <vector>

class IContent
{
public:
    virtual ~IContent();

    virtual std::string toString(const std::vector<uint8_t>& datas, bool isSend) = 0;
};

#endif // ICONTENT_H
