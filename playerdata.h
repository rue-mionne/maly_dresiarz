#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "nothreadseventpacktm.h"

class PlayerData
{
public:
    PlayerData(NoThreadsEventPackTM* events);
    int getSzacun();
    int setSzacun(int added_szacun);
    int getKasa();
    int setKasa(int added_szacun);
    int getHaracze();
    int setHaracze(int added_szacun);
    int getBMW();
    int setBMW(int added_szacun);
private:
    NoThreadsEventPackTM* poCoMuteksy;
    int Szacun;
    int Kasa;
    int Haracze;
    int BMW;
};

#endif // PLAYERDATA_H
