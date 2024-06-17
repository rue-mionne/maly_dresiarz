#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>
#include "playerdata.h"

class player
{
public:
    player();
    std::string getName();
    void setName(std::string name);
    std::shared_ptr<PlayerData> getPlayerData();
    void rejestrujSledzia(PlayerClient* sledz){poCoMuteksy.addListenerAgent(sledz);}
private:
    NoThreadsEventPackTM poCoMuteksy;
    std::shared_ptr<PlayerData> playerData = std::make_shared<PlayerData>(&poCoMuteksy);
    std::string name;
};

#endif // PLAYER_H
