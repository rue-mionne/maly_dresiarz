#ifndef INBOX_H
#define INBOX_H

#include <qlineedit.h>
#include <qpushbutton.h>
#include <QTableWidget>

enum class EVENT_TYPE{
    fillName,
    choseAction,
    updateRank,
    fillRank,
    npcReg,
    npcAct
};

class Inbox
{
public:
    Inbox(QLineEdit* nameBox, QPushButton* enableButton, QTableWidget* ranking, QLineEdit* npcact, QLineEdit* npcreg);
    void Notify(EVENT_TYPE event, std::string name, int ID=0);
private:
    QLineEdit* nameBox;
    QPushButton* enableButton;
    QTableWidget* dresiarzRank;
    QLineEdit* npcact;
    QLineEdit* npcreg;
};

#endif // INBOX_H
