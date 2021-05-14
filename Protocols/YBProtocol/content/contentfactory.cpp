#include "contentfactory.h"
#include "../ybframe.h"
#include "contentnakerror.h"
#include "contentqueryaddr.h"
#include "contentquerystatus.h"
#include "contentqueryversion.h"
#include "contentreportstatus.h"
#include "contentsettingaddr.h"
#include "contentsettingstatus.h"
#include "contentforcesetaddr.h"
#include "contentsetsensornum.h"

ContentFactory::ContentFactory()
{

}

IContent *ContentFactory::createContent(uint8_t funCode, const std::vector<uint8_t> &datas)
{
    IContent* content = nullptr;
    switch (funCode) {
    case eYBFunCode::NAKCode:
        content = new ContentNAKError(datas.at(0), datas.at(1));
        break;
    case eYBFunCode::SetStatusCode:
        content = new ContentSettingStatus(datas.at(0));
        break;
    case eYBFunCode::QueryStatusCode:
        content = datas.empty() ? new ContentQueryStatus() : new ContentQueryStatus(datas.at(0), datas.at(1));
        break;
    case eYBFunCode::QueryVersionCode:
        content = new ContentQueryVersion(datas);
        break;
    case eYBFunCode::SetAddressCode:
        content = new ContentSettingAddr(datas.at(0));
        break;
    case eYBFunCode::ReportStatusCode:
        content = new ContentReportStatus(datas.at(0), datas.at(1));
        break;
    case eYBFunCode::SetSensorNumCode:
        content  = new ContentSetSensorNum(datas.at(0));
        break;
    case eYBFunCode::UpgradeCode:
        break;
    case eYBFunCode::ForceSettingAddrCode:
        content = datas.empty() ? new ContentForceSetAddr() : new ContentForceSetAddr(datas.at(0), datas.at(1));
        break;
    case eYBFunCode::QueryAddrCode:
        content = datas.empty() ? new ContentQueryAddr() : new ContentQueryAddr(datas.at(0), datas.at(1));
        break;
    }

    return content;
}
