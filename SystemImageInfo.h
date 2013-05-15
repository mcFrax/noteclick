#ifndef SYSTEMIMAGEINFO_H
#define SYSTEMIMAGEINFO_H

#include <QString>

class QPixmap;

class SystemImageInfo
{
    QString fileNameVal;
public:
    SystemImageInfo();
    SystemImageInfo(const QString& fileName);

    QString fileName() const;
    void setFileName(const QString& fileName);

    QPixmap pixmap() const;
};

#endif // SYSTEMIMAGEINFO_H
