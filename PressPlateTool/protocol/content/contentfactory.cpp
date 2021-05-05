#include "contentfactory.h"
#include "../ybframe.h"
#include "contentqueryaddr.h"
#include "contentquerystatus.h"
#include "contentqueryversion.h"
#include "contentreportstatus.h"
#include "contentsettingaddr.h"
#include "contentsettingstatus.h"

ContentFactory::ContentFactory()
{

}

IContent *ContentFactory::createContent(uint8_t funCode)
{
    IContent* content = nullptr;
    switch (funCode) {
    case eYBFunCode::SettingStatusCode:
        content = new ContentSettingStatus();
        break;
    case eYBFunCode::QueryStatusCode:
        content = new ContentQueryStatus();
        break;
    case eYBFunCode::QueryVersionCode:
        content = new ContentQueryVersion();
        break;
    case eYBFunCode::SettingAddrCode:
        content = new ContentSettingAddr();
        break;
    case eYBFunCode::ReportStatusCode:
        content = new ContentReportStatus();
        break;
    case eYBFunCode::UpgradeCode:
        break;
    case eYBFunCode::ForceSettingAddrCode:
        break;
    case eYBFunCode::QueryAddrCode:
        content = new ContentQueryAddr();
        break;
    }

    return content;
}
