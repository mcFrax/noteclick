#ifndef SCOREMODEL_H
#define SCOREMODEL_H

#include <QObject>

namespace Model
{

class ScoreModel : public QObject
{
    Q_OBJECT
public:
    explicit ScoreModel(QObject *parent = 0);
    
signals:
//    void structureChanged(StructureChange change);
//    void systemChanged(ModelId::IdType systemId, SystemChange change);
//    void changed(ScoreChange change);
    void error(QString what); //byc moze trzeba jakos rozdzielic fatal error/non-fatal error
    
public slots:
//    void userAction(UserAction action);
};

}

#endif // SCOREMODEL_H
