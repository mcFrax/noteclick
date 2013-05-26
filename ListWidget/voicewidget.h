#ifndef VOICEWIDGET_H
#define VOICEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QRadioButton>

#include "erasebutton.h"
#include "listitem.h"
#include "score.h"

class VoiceWidget : public ListItem
{
    Q_OBJECT
public:
    explicit VoiceWidget(QString name, Score *score, QWidget *parent = 0);
    
    virtual void setText(QString name);

    void setSelected(bool);

signals:
    void clicked();
    void voiceChecked(void *p, bool state);
    void voiceSelected(void *p, bool state);

public slots:
    void erase();
    void checked();
    void selected();
protected:
    Score *score;
    QLabel *name;
    QHBoxLayout *layout;
    QPushButton *eraseButton;
    QRadioButton *radioButton;
    QCheckBox *checkBox;

    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // VOICEWIDGET_H
