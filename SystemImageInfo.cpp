#include "SystemImageInfo.h"

#include <QPixmap>

#include <poppler-qt4.h>

SystemImageInfo::SystemImageInfo()
{
}

SystemImageInfo::SystemImageInfo(QString fileName,
                                 QTransform transformation,
                                 int pageNumber, QRect frame)
    : fileNameVal(fileName), transformation(transformation),
      pageNumber(pageNumber), frame(frame)
{
}

SystemImageInfo::SystemImageInfo(QPixmap qpixmap,
                                 QTransform transformation,
                                 int pageNumber, QRect frame)
    : qpixmap(qpixmap), transformation(transformation),
      pageNumber(pageNumber), frame(frame)
{
}

bool SystemImageInfo::isNull() const
{
    return (fileNameVal.isEmpty())&&(qpixmap.isNull());
}

QString SystemImageInfo::fileName() const
{
    return fileNameVal;
}

void SystemImageInfo::remember()
{
//    remember = True;
    qpixmap = transformed();
    fileNameVal.clear();

}



void SystemImageInfo::setFileName(const QString &fileName)
{
    fileNameVal = fileName;
}

QPixmap SystemImageInfo::pixmap() const
{
    if (qpixmap.isNull()){
        Poppler::Document *doc = Poppler::Document::load(fileNameVal);
        Poppler::Page * page = doc->page(pageNumber);
        QSize size = page ->pageSize();
        int scaleFactor = 1;
        QImage qimage = page->renderToImage(
                    scaleFactor * size.width(),
                    scaleFactor * size.height());
        return QPixmap::fromImage(qimage);
    } else {
        return qpixmap;
    }
}

QPixmap SystemImageInfo::transformed() const
{   
    QPixmap qmap = pixmap().copy(frame);
    return qmap.transformed(transformation, Qt::FastTransformation);
}
