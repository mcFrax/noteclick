#ifndef SYSTEMIMAGEDIALOG_H
#define SYSTEMIMAGEDIALOG_H

#include <QDialog>
#include <QFileDialog>

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

private:
    Ui::SystemImageDialog *ui;
    QString fileName;
    int sizeScale;
};


#endif // SYSTEMIMAGEDIALOG_H
