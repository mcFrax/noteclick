#ifndef SYSTEMIMAGEDIALOG_H
#define SYSTEMIMAGEDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <SystemImageInfo.h>

namespace Ui {
class SystemImageDialog;
}

class SystemImageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SystemImageDialog(QWidget *parent = 0);
    ~SystemImageDialog();
    int exec();
    
private slots:
    void on_resizer_valueChanged(int value);

    void on_spinBox_valueChanged(int arg1);

    void on_horizontalSlider_valueChanged(int value);

    void on_vertical_valueChanged(int value);

    void on_dial_valueChanged(int value);

    void on_graphicsView_objectNameChanged(const QString &objectName);

private:
    Ui::SystemImageDialog *ui;
    QString fileName;
    int sizeScale;
    QTransform transformation = QTransform();
    SystemImageInfo pic;
    QRect frame;
    int rotate;
    int page;
};


#endif // SYSTEMIMAGEDIALOG_H
