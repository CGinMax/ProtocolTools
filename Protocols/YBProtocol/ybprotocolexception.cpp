#include "ybprotocolexception.h"

YBProtocolException::YBProtocolException(eYBParseResult result, const std::string &str)
    : std::logic_error(str)
    , m_parseResult(result)
{

}

eYBParseResult YBProtocolException::result() const
{
    return m_parseResult;
}
