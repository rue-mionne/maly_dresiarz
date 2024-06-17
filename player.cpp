#include "player.h"

player::player() {

}

std::shared_ptr<PlayerData> player::getPlayerData(){
    return playerData;
}

std::string player::getName(){
    return name;
}

void player::setName(std::string name){
    this->name=name;
    poCoMuteksy.Notify(TypeUpdate::Name);
}

