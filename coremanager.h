#ifndef COREMANAGER_H
#define COREMANAGER_H

#include "playerclient.h"
#include <map>
#include <string>
#include <vector>


class CoreManager
{
public:
    CoreManager(bool host);
    void rejestrujDresiarza(player* gracz);
    void wykonajAkcje(int akcja, std::string nazwa);
    void wywolajKolejnegoKlienta();
    int getTuraCount(){return turaCounter;}
    void addPlayerClient(PlayerClient klient);
    std::shared_ptr<PlayerData> getDresiarz(std::string name);
    int npcFIX(){
        if(turaCounter!=12){
            active_player_id++;
            if((clientList.size()<=active_player_id)){
                active_player_id=0;
                turaCounter++;
            }
            return 0;
        }
        else return -1;
    }
    std::vector<PlayerClient>* getClientList(){return &clientList;}
private:
    bool isHost;
    int turaCounter=0;
    int active_player_id=0;
    std::map<std::string, std::shared_ptr<PlayerData>> listaDresiarzy;
    std::vector<PlayerClient> clientList;
    void notifyClients();

};

#endif // COREMANAGER_H
