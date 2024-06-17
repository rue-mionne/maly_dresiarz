#include "malydresiarz.h"
#include "./ui_MalyDresiarzUI.h"
#include <string>

MalyDresiarz::MalyDresiarz(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MalyDresiarz)
{
    ui->setupUi(this);

    inbox= new Inbox(ui->PlayerName, ui->MakeMove, ui->DresiarzRanking, ui->npcact, ui->npcreg);
}

MalyDresiarz::~MalyDresiarz()
{
    delete ui;
}

void MalyDresiarz::on_RadioTypeLokalna_toggled(){
    mode_selected=true;
    CheckIfValidStart();
}

void MalyDresiarz::on_SpinPlayers_valueChanged(int new_val){
    players=new_val;
    total_players=players+npcs;
    CheckIfValidStart();
}

void MalyDresiarz::on_SpinComputerPlayers_valueChanged(int new_val){
    npcs=new_val;
    total_players=players+npcs;
    CheckIfValidStart();
}

bool MalyDresiarz::CheckIfValidStart(){
    if(mode_selected&&total_players>1&&players>1){
        ui->StartButton->setEnabled(true);
        return true;
    }
    else{
        ui->StartButton->setEnabled(false);
    return false;
}
}

void MalyDresiarz::on_StartButton_clicked(){
    ui->Gra->setEnabled(true);
    ui->Start->setVisible(false);
    ui->Start->setEnabled(false);
    ui->Gra->setVisible(true);//zamierzony bug wizualny: zakładki i tak mają być bezużyteczne, ale nie do końca wiem, jak je schować
    manager=new CoreManager(true);
    std::vector<PlayerClient> klienci;
    if(ui->RadioTypeLokalna->isChecked()){
        int ID=0;
        for(int i=0; i<players;i++){
            PlayerClient klient = PlayerClient(Mode::local, Player_Type::playable,ID, inbox);
            manager->addPlayerClient(klient);
            klienci.emplace_back(klient);
            ID++;
        }
        for(int i=0;i<npcs;i++){
            PlayerClient klient = PlayerClient(Mode::local, Player_Type::npc,ID, inbox);
            manager->addPlayerClient(klient);
            klienci.emplace_back(klient);
            ID++;
        }
    }
    ui->DresiarzRanking->setColumnCount(2);
    ui->DresiarzRanking->setRowCount(players+npcs);
    manager->wywolajKolejnegoKlienta();
}


void MalyDresiarz::on_PlayerName_textChanged(const QString &text){
    if(!ui->PlayerName->text().isEmpty()){
        if(manager->getDresiarz(text.toStdString())!=nullptr){
            std::shared_ptr<PlayerData> dane = manager->getDresiarz(text.toStdString());
            ui->BMWStat->setText(QString::fromStdString("BMW: "+std::to_string(dane->getBMW())));
            ui->HaraczeStat->setText(QString::fromStdString("Haracze: "+std::to_string(dane->getHaracze())));
            ui->KasaStat->setText(QString::fromStdString("Kasa: "+std::to_string(dane->getKasa())));
            ui->SzacunStat->setText(QString::fromStdString("Szacun: "+std::to_string(dane->getSzacun())));
            ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(dane->getBMW())));
            ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(dane->getHaracze())));
            ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(dane->getKasa())));
            ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(dane->getSzacun())));
            ui->BMWRadio->setChecked(false);
            ui->HaraczRadio->setChecked(false);
            ui->IwanRadio->setChecked(false);
            ui->LansRadio->setChecked(false);
            ui->DoRobotyRadio->setChecked(false);
            if(dane->getKasa()<4)
                ui->HaraczRadio->setEnabled(false);
            else
                ui->HaraczRadio->setEnabled(true);
            ui->TuraCounter->setText(QString::fromStdString("Pozostało: " + std::to_string(11-manager->getTuraCount()) + " tur."));
        }
    }
    else
        ui->Zatwierdz->setEnabled(true);
}

void MalyDresiarz::on_Zatwierdz_clicked(){
    std::vector<PlayerClient>* lista = manager->getClientList();
    PlayerClient* client = &(lista->at(ID));
    player* gracz = new player();
    client->setGracz(gracz);
    gracz->rejestrujSledzia(client);
    gracz->setName(ui->PlayerName->text().toStdString());
    IDMap.emplace(gracz->getName(), ID);
    ID++;
    manager->rejestrujDresiarza(gracz);
    ui->Zatwierdz->setEnabled(false);
    ui->PlayerName->setEnabled(false);
    manager->npcFIX();
    manager->wywolajKolejnegoKlienta();
}

void MalyDresiarz::on_npcreg_textChanged(const QString &text){
    std::vector<PlayerClient>* lista = manager->getClientList();
    PlayerClient* client = &(lista->at(std::stoi(text.toStdString())));
    player* gracz = client->getPlayer();
    manager->rejestrujDresiarza(gracz);
    manager->npcFIX();
    manager->wywolajKolejnegoKlienta();
}

void MalyDresiarz::on_BMWRadio_toggled(){
    if(manager->getDresiarz(ui->PlayerName->text().toStdString())!=nullptr){
        ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getBMW()+1)));
        ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getKasa())));
        ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getHaracze())));
        ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getSzacun())));
    }
}

void MalyDresiarz::on_DoRobotyRadio_toggled(){
    if(manager->getDresiarz(ui->PlayerName->text().toStdString())!=nullptr){
        ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getKasa()+2)));
        ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getBMW())));
        ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getHaracze())));
        ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getSzacun())));
    }
}

void MalyDresiarz::on_HaraczRadio_toggled(){
    if(manager->getDresiarz(ui->PlayerName->text().toStdString())!=nullptr){
        ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getKasa()-4)));
        ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getHaracze()+1)));
        ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getSzacun())));
        ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getBMW())));
    }
}

void MalyDresiarz::on_IwanRadio_toggled(){
    if(manager->getDresiarz(ui->PlayerName->text().toStdString())!=nullptr){
        ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getKasa())));
        ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getSzacun())));
        ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getBMW())));
        ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getHaracze())));
    }
}

void MalyDresiarz::on_LansRadio_toggled(){
    if(manager->getDresiarz(ui->PlayerName->text().toStdString())!=nullptr){
        ui->SzacunPred->setText(QString::fromStdString("Szacun: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getSzacun()+1)));
        ui->KasaPred->setText(QString::fromStdString("Kasa: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getKasa())));
        ui->BMWPred->setText(QString::fromStdString("BMW: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getBMW())));
        ui->HaraczePred->setText(QString::fromStdString("Haracze: "+std::to_string(manager->getDresiarz(ui->PlayerName->text().toStdString())->getHaracze())));
    }
}

void MalyDresiarz::on_MakeMove_clicked(){
    int akcja=0;
    if(ui->LansRadio->isChecked()) akcja =1;
    if(ui->DoRobotyRadio->isChecked()) akcja=2;
    if(ui->HaraczRadio->isChecked()) akcja=3;
    if(ui->BMWRadio->isChecked()) akcja=4;
    if(ui->IwanRadio->isChecked()) akcja=5;
    int ended=0;
    if(akcja!=0){
        ended = manager->npcFIX();
        if(ended!=-1){
            manager->wykonajAkcje(akcja, ui->PlayerName->text().toStdString());
            ui->DresiarzRanking->sortItems(1, Qt::DescendingOrder);
        }
    }
    if(ended == -1){
        QBrush pedzel;
        pedzel.setColor(Qt::GlobalColor::green);
        ui->DresiarzRanking->item(0,0)->setForeground(pedzel);
        ui->DresiarzRanking->item(0,1)->setForeground(pedzel);
        ui->DresiarzRanking->item(0,0)->setBackground(pedzel);
        ui->DresiarzRanking->item(0,1)->setBackground(pedzel);
    }
}

void MalyDresiarz::on_npcact_textChanged(const QString &text){
    std::string data = text.toStdString();
    std::string graczname = data.substr(0, data.find(" "));
    data.erase(0, data.find(" ")+1);
    int akcja = std::stoi(data);
    int ended = manager->npcFIX();
    manager->wykonajAkcje(akcja,graczname);
    if(ended == -1){
        QBrush pedzel;
        pedzel.setColor(Qt::GlobalColor::green);
        ui->DresiarzRanking->item(0,0)->setForeground(pedzel);
        ui->DresiarzRanking->item(0,1)->setForeground(pedzel);
        ui->DresiarzRanking->item(0,0)->setBackground(pedzel);
        ui->DresiarzRanking->item(0,1)->setBackground(pedzel);

    }
}
