#include "SystemImageInfo.h"

#include <QPixmap>

SystemImageInfo::SystemImageInfo()
{
}

SystemImageInfo::SystemImageInfo(const QString &fileName)
    : fileNameVal(fileName)
    Poppler::Document *doc = Poppler::Document::load(fileName);
    QImage qimage = doc->page(currentPage)->renderToImage(
                            scaleFactor * physicalDpiX(),
                            scaleFactor * physicalDpiY());
    image = QPixmap::fromImage(qimage);
{
}

bool SystemImageInfo::isNull() const
{
    return (fileNameVal==NULL)&&(QPixmap==NULL);
}

QString SystemImageInfo::fileName() const
{
    return fileNameVal;
}

voif SystemImageInfo::remember()
{
    remember = True;
    image = image.transformed();
}


void SystemImageInfo::setFileName(const QString &fileName)
{
    fileNameVal = fileName;
}

QPixmap SystemImageInfo::pixmap() const
{
    return QPixmap(fileName());
}

QPixmap SystemImageInfo::transformed() const
{   
    QPixmap qmap = SystemImageInfo.pixmap().copy(frame);
    return qmap.transformed(&transformation, 
        Qt::TransformationModemode=Qt::FastTransformation);
}
