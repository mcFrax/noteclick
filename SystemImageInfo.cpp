#include "SystemImageInfo.h"

#include <QPixmap>

#include <poppler/qt4/poppler-qt4.h>

SystemImageInfo::SystemImageInfo()
{
}

SystemImageInfo::SystemImageInfo(const QString &fileName)
    : fileNameVal(fileName)
{
    pageNumber = 1;
    Poppler::Document *doc = Poppler::Document::load(fileName);
    QImage qimage = doc->page(pageNumber)->renderToImage(
                            scaleFactor * physicalDpiX(),
                            scaleFactor * physicalDpiY());
    image = QPixmap::fromImage(qimage);
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
//    remember = True;
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
