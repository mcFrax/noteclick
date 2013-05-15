#ifndef SYSTEMIMAGEINFO_H
#define SYSTEMIMAGEINFO_H

#include <QString>

class SystemImageInfo
{
    QString fileNameVal;
public:
    SystemImageInfo();
    SystemImageInfo(const QString& fileName);

    QString fileName() const;
    void setFileName(const QString& fileName);
};

#endif // SYSTEMIMAGEINFO_H
