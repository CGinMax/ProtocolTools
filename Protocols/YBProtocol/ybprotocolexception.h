#ifndef YBPROTOCOLEXCEPTION_H
#define YBPROTOCOLEXCEPTION_H
#include <stdexcept>
#include "ybframeenums.h"
#include "../protocols_global.h"
class PROTOCOLSSHARED_EXPORT YBProtocolException : public std::logic_error
{
public:
    explicit YBProtocolException(eYBParseResult result, const std::string& str);
    eYBParseResult result() const;

private:
    eYBParseResult m_parseResult;
};

#endif // YBPROTOCOLEXCEPTION_H
