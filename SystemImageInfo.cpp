#include "SystemImageInfo.h"

SystemImageInfo::SystemImageInfo()
{
}

SystemImageInfo::SystemImageInfo(const QString &fileName)
    : fileNameVal(fileName)
{
}


void SystemImageInfo::setFileName(const QString &fileName)
{
    fileNameVal = fileName;
}
