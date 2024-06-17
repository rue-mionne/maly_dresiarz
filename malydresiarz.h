#ifndef MALYDRESIARZ_H
#define MALYDRESIARZ_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include "coremanager.h"
#include "inbox.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MalyDresiarz;
}
QT_END_NAMESPACE

class MalyDresiarz : public QMainWindow
{
    Q_OBJECT

public slots:
    void on_RadioTypeLokalna_toggled();
    void on_SpinPlayers_valueChanged(int);
    void on_SpinComputerPlayers_valueChanged(int);
    void on_StartButton_clicked();
    void on_PlayerName_textChanged(const QString &text);
    void on_Zatwierdz_clicked();
    void on_BMWRadio_toggled();
    void on_DoRobotyRadio_toggled();
    void on_HaraczRadio_toggled();
    void on_IwanRadio_toggled();
    void on_LansRadio_toggled();
    void on_MakeMove_clicked();
    void on_npcact_textChanged(const QString &text);
    void on_npcreg_textChanged(const QString &text);

public:
    MalyDresiarz(QWidget *parent = nullptr);
    ~MalyDresiarz();

private:
    Ui::MalyDresiarz *ui;
    CoreManager* manager;
    Inbox* inbox;
    std::map<std::string, int> IDMap;

    bool mode_selected=false;
    int total_players=0;
    int npcs=0;
    int players=0;
    int ID=0;
    bool CheckIfValidStart();
};
#endif // MALYDRESIARZ_H
