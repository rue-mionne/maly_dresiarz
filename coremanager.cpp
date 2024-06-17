#include "coremanager.h"


CoreManager::CoreManager(bool host) {
    isHost=host;
}

void CoreManager::rejestrujDresiarza(player* gracz){
    listaDresiarzy.emplace(gracz->getName(),gracz->getPlayerData());
//    clientList.at((active_player_id-1+clientList.size())%clientList.size()).setGracz(gracz);//don't touch me part; zmiany grożą zawaleniem kodu; potrzeba refaktoryzacji
}

void CoreManager::wykonajAkcje(int akcja, std::string nazwa){
    switch(akcja){
    case 1:{
            auto dresiarz = listaDresiarzy.find(nazwa);
            dresiarz->second->setSzacun(1);
            break;}
    case 2:{
            auto dresiarz = listaDresiarzy.find(nazwa);
            dresiarz->second->setKasa(2);
            break;}
    case 3:{
            auto dresiarz = listaDresiarzy.find(nazwa);
            if(dresiarz->second->getKasa()>=4){
                dresiarz->second->setKasa(-4);
                dresiarz->second->setHaracze(1);
            }
            break;}
    case 4:{
            auto dresiarz = listaDresiarzy.find(nazwa);
            dresiarz->second->setBMW(1);
            break;}
    case 5:{
            for(auto dresiarz : listaDresiarzy){
                if(dresiarz.first!=nazwa){
                    dresiarz.second->setKasa(-1);
                }
            }
            break;}
    }
    wywolajKolejnegoKlienta();
}

void CoreManager::addPlayerClient(PlayerClient klient){
    clientList.emplace_back(klient);
}

void CoreManager::wywolajKolejnegoKlienta(){
    if(turaCounter!=12){
        clientList.at(active_player_id).Notify(this);
    }

}

std::shared_ptr<PlayerData> CoreManager::getDresiarz(std::string name){
    if(listaDresiarzy.find(name)!=listaDresiarzy.end())
        return listaDresiarzy.find(name)->second;
    else
        return nullptr;
}
