#include "SystemImageInfo.h"

#include <QPixmap>

SystemImageInfo::SystemImageInfo()
{
}

SystemImageInfo::SystemImageInfo(const QString &fileName)
    : fileNameVal(fileName)
{
}

QString SystemImageInfo::fileName() const
{
    return fileNameVal;
}


void SystemImageInfo::setFileName(const QString &fileName)
{
    fileNameVal = fileName;
}

QPixmap SystemImageInfo::pixmap() const
{
    return QPixmap(fileName());
}
