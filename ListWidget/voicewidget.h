#ifndef VOICEWIDGET_H
#define VOICEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "erasebutton.h"
#include "listitem.h"
#include "score.h"

class VoiceWidget : public ListItem
{
    Q_OBJECT
public:
    explicit VoiceWidget(QString name, Score *score, QWidget *parent = 0);
    
    virtual void setText(QString name);

signals:
    void clicked();

public slots:
    void erase();
protected:
    Score *score;
    QLabel *name;
    QHBoxLayout *layout;
    QPushButton *eraseButton;

    void paintEvent(QPaintEvent *);
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

};

#endif // VOICEWIDGET_H
