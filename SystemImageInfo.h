#ifndef SYSTEMIMAGEINFO_H
#define SYSTEMIMAGEINFO_H

#include <QString>
#include <QPixmap>

class SystemImageInfo
{
    QString fileNameVal;
    int pageNumber;
    QTransform transformation;
    QRect frame;
    QPixmap qpixmap;
//    bool remember;
public:
    SystemImageInfo();
    SystemImageInfo(const QString fileName,
                    QTransform transformation,
                    int pageNumber, QRect frame);
    SystemImageInfo(QPixmap qpixmap,
                    QTransform transformation,
                    int pageNumber, QRect frame);

    bool isNull() const;
    QString fileName() const;
    void setFileName(const QString& fileName);
    QPixmap pixmap() const;
    QPixmap transformed() const;
    void remember();
};

#endif // SYSTEMIMAGEINFO_H
