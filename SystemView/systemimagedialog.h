#ifndef SYSTEMIMAGEDIALOG_H
#define SYSTEMIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class SystemImageDialog;
}

class SystemImageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SystemImageDialog(QWidget *parent = 0);
    ~SystemImageDialog();
    
private:
    Ui::SystemImageDialog *ui;
};

#endif // SYSTEMIMAGEDIALOG_H
