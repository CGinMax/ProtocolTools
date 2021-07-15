#include "contentnakerror.h"
#include "../../convert.h"

ContentNAKError::ContentNAKError(uint8_t errorFunctionCode, uint8_t errorNakCode)
    : m_errFunCode(errorFunctionCode)
    , m_nakFunCode(errorNakCode)
{
    m_funCode = 0x01;
}


std::string ContentNAKError::toString(bool isSend)
{
    (void)isSend;
    std::string result = u8",NAK错误, 错误功能码:";
    result += Convert::num2HexString(m_errFunCode);//hex
    result += u8", NAK错误码:";
    result += Convert::num2HexString(m_nakFunCode);
    return result;
}

std::vector<uint8_t> ContentNAKError::toByteVector()
{
    return {m_errFunCode, m_nakFunCode};
}
