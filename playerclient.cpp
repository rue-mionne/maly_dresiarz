#include "playerclient.h"
#include "coremanager.h"
#include "inbox.h"

PlayerClient::PlayerClient(Mode playMode, Player_Type play_type, int ID, Inbox* inbox) {
    PlayMode=playMode;
    playType=play_type;
    this->ID=ID;
    this->inbox=inbox;
}

void PlayerClient::Notify(CoreManager* manager){
    if(PlayMode==Mode::local){
        if(gracz==nullptr){
            if(playType==Player_Type::npc){
                gracz=new player();
                gracz->rejestrujSledzia(this);
                gracz->setName("Dresiarz" + std::to_string(ID));

                inbox->Notify(EVENT_TYPE::npcReg,"",ID);

            }
            if(playType==Player_Type::playable){
                gracz=new player();
                gracz->rejestrujSledzia(this);
                inbox->Notify(EVENT_TYPE::fillName, "");
            }


        }
        else{
            int akcja;
            gracz->getPlayerData()->setKasa(0);
            for(int i=0; i<gracz->getPlayerData()->getBMW();i++){
                if(gracz->getPlayerData()->getKasa()>=2){
                    gracz->getPlayerData()->setKasa(-2);
                    gracz->getPlayerData()->setSzacun(3);
                }
                else
                    gracz->getPlayerData()->setSzacun(-2);
            }

            if(playType==Player_Type::npc){
                akcja = std::rand()%5+1;
                if(akcja==4&&gracz->getPlayerData()->getKasa()<4){
                    akcja=1;
                }

                inbox->Notify(EVENT_TYPE::npcAct,gracz->getName(), akcja);



            }
            if(playType==Player_Type::playable){
                inbox->Notify(EVENT_TYPE::choseAction, gracz->getName());
            }
        }
    }
}

void PlayerClient::statsChange(TypeUpdate typZmian){
    switch(typZmian){
        case TypeUpdate::Name:
            inbox->Notify(EVENT_TYPE::fillRank, gracz->getName(), ID);
            break;
        case TypeUpdate::Szacun:
            inbox->Notify(EVENT_TYPE::updateRank, gracz->getName(), gracz->getPlayerData()->getSzacun());
            break;
        }
}
