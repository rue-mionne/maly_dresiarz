#include "inbox.h"

Inbox::Inbox(QLineEdit* nameBox, QPushButton* enableButton, QTableWidget* ranking, QLineEdit* npcact, QLineEdit* npcreg) {
    this->nameBox=nameBox;
    this->enableButton=enableButton;
    this->dresiarzRank=ranking;
    this->npcact=npcact;
    this->npcreg=npcreg;
}

void Inbox::Notify(EVENT_TYPE event, std::string name, int ID){
    int row;
    QTableWidgetItem* szac;
    switch(event){
        case EVENT_TYPE::fillName:
            nameBox->clear();
            nameBox->setPlaceholderText("Wpisz nazwę dresiarza i naciśnij ENTER");
            nameBox->setEnabled(true);
            enableButton->setEnabled(false);
        break;
        case EVENT_TYPE::choseAction:
            nameBox->setText(QString::fromStdString(name));
            enableButton->setEnabled(true);
            break;
        case EVENT_TYPE::updateRank:
            row = dresiarzRank->findItems(QString::fromStdString(name),Qt::MatchFlag::MatchFixedString).first()->row();
            szac = new QTableWidgetItem();
            szac->setData(Qt::DisplayRole, ID);
            dresiarzRank->setItem(row, 1, szac);
            break;
        case EVENT_TYPE::fillRank:
            dresiarzRank->setItem(ID, 0, new QTableWidgetItem(QString::fromStdString(name)));
            szac = new QTableWidgetItem();
            szac->setData(Qt::DisplayRole, 0);
            dresiarzRank->setItem(ID, 1, szac);
            break;
        case EVENT_TYPE::npcAct:
            npcact->setText(QString::fromStdString(name+" "+std::to_string(ID)));
            break;
        case EVENT_TYPE::npcReg:
            npcreg->setText(QString::fromStdString(std::to_string(ID)));
            break;
    }
}
