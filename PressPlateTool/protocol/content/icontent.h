#ifndef ICONTENT_H
#define ICONTENT_H

#include <string>
#include <cstdint>
#include <vector>

class IContent
{
public:
    virtual ~IContent();

    virtual std::string toString(bool isSend) = 0;
    virtual std::vector<uint8_t> toByteVector() = 0;
};

#endif // ICONTENT_H
