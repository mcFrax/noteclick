#include "spinbox.h"

using namespace SpinBoxNamespace;

SpinBox::SpinBox(QWidget *parent) :
    QWidget(parent)
{

    layout = new QHBoxLayout();
    plusLayout = new QVBoxLayout();
    spinbox = new QSpinBox();

    plus = new QPushButton("+");
    minus = new QPushButton("-");

    plus->setFixedHeight(23);
    plus->setFixedWidth(23);
    minus->setFixedHeight(23);
    minus->setFixedWidth(23);

    plusLayout->setMargin(0);
    plusLayout->setSpacing(0);

    spinbox->setRange(0, 0);

    plusLayout->addWidget(plus);
    //plusLayout->addWidget(minus);
    layout->addLayout(plusLayout);
    layout->addWidget(spinbox);



    setLayout(layout);

    // connecty

    connect(spinbox, SIGNAL(valueChanged(int)), this, SLOT(changeScore(int)));
    connect(plus, SIGNAL(clicked()), this, SLOT(addScore()));
    connect(minus, SIGNAL(clicked()), this, SLOT(eraseScore()));

}

void SpinBox::setIdList(QList<IdType> &list)
{
    idList = list;
}

void SpinBox::scoreChanged(ScoreChange change)
{
    try
    {
        switch (change.category)
        {
            case ScoreChange::StructureChanged:
                handleStructureChange(change);
                return;
            case ScoreChange::SystemChanged:
                //To nas nie obchodzi.
                return;
            case ScoreChange::ScoreChanged:
                //To nas nie obchodzi.
                return;
            //Nie wstawiac default!
            //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
        }

        //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.category:
        emit error(tr("Invalid ScoreChange::category value ")+QString::number(change.category));
    }
    catch (std::bad_cast &e)
    {
        emit error(tr("std::bad_cast caught during ScoreChange handling: ")+e.what()+'\n'
                   +"VSA typeid = "+change.args.typeName());
    }
}


void SpinBox::handleStructureChange(ScoreChange change)
{
    IdType systemId;

    switch (static_cast<ScoreChange::StructureChangeEnum>(change.change))
    {

    case ScoreChange::SystemCreated:          //(IdType id: IdType parent_id)
        change.args.unpackTo(systemId);
        systemAdded(systemId);
        return;
    case ScoreChange::SystemObjectErased:          //(IdType id: IdType parent_id)
        change.args.unpackTo(systemId);
        systemErased(systemId);
        return;

        //Nie wstawiac default!
        //Chodzi o to, zeby dostac warn w przypadku nieobslugiwania czegos.
    }

    //Tu trafiamy tylko w przypadku niepoprawnej wartosci action.action:
    emit error(tr("Invalid or unhandled ScoreChanged::change value (as ScoreChanged::StructureChanged) ")
            +QString::number(change.change));
}

void SpinBox::systemErased(IdType id)
{

}

void SpinBox::systemAdded(IdType id)
{


}


void SpinBox::changeScore()
{

}

void SpinBox::addScore()
{

}

void SpinBox::eraseScore()
{

}
