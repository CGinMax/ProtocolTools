#include "contentnakerror.h"
#include "../utilhelper.h"

ContentNAKError::ContentNAKError(uint8_t funCode, uint8_t errorCode)
    : funCode(funCode)
    , errorCode(errorCode)
{
}


std::string ContentNAKError::toString(bool isSend)
{
    (void)isSend;
    std::string result = u8"NAK错误, 错误功能码:";
    result += UtilHelper::num2HexString(funCode);//hex
    result += u8", NAK错误码:";
    result += UtilHelper::num2HexString(errorCode);
    return result;
}

std::vector<uint8_t> ContentNAKError::toByteVector()
{
    return {funCode, errorCode};
}
