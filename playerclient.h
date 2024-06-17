#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H

#include "player.h"
#include "inbox.h"

class CoreManager;

enum class Mode{
    online,
    local
};

enum class Player_Type{
    playable,
    npc
};



class PlayerClient
{
private:
    Mode PlayMode;
    int ID;
    Player_Type playType;
    player* gracz=nullptr;
    Inbox* inbox=nullptr;
public:

    PlayerClient(Mode playMode, Player_Type play_type, int ID, Inbox* inbox);
    void Notify(CoreManager* manager);
    void setGracz(player* gracz){this->gracz=gracz;}
    void statsChange(TypeUpdate typZmian);
    player* getPlayer(){return gracz;}
    std::string getName(){gracz->getName();}
};



#endif // PLAYERCLIENT_H
