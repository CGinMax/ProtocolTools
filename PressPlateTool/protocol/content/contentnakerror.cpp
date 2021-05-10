#include "contentnakerror.h"
#include "../utilhelper.h"

ContentNAKError::ContentNAKError(uint8_t errorFunctionCode, uint8_t errorNakCode)
    : errFunCode(errorFunctionCode)
    , nakFunCode(errorNakCode)
{
    funCode = 0x01;
}


std::string ContentNAKError::toString(bool isSend)
{
    (void)isSend;
    std::string result = u8"NAK错误, 错误功能码:";
    result += UtilHelper::num2HexString(errFunCode);//hex
    result += u8", NAK错误码:";
    result += UtilHelper::num2HexString(nakFunCode);
    return result;
}

std::vector<uint8_t> ContentNAKError::toByteVector()
{
    return {errFunCode, nakFunCode};
}
