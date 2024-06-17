#include "playerdata.h"

PlayerData::PlayerData(NoThreadsEventPackTM* events) {
    Szacun=0;
    Kasa=0;
    Haracze=0;
    BMW=0;
    poCoMuteksy=events;
}

int PlayerData::getSzacun(){
    return Szacun;
}

int PlayerData::setSzacun(int added_szacun){
    Szacun+=added_szacun;
    if(Szacun<0){
        Szacun=0;
    }
    poCoMuteksy->Notify(TypeUpdate::Szacun);
    return Szacun;
}

int PlayerData::getKasa(){
    return Kasa;
}

int PlayerData::setKasa(int added_kasa){
    Kasa+=added_kasa;
    if(Kasa<0){
        Kasa=0;
    }
    return Kasa;
}

int PlayerData::getHaracze(){
    return Haracze;
}

int PlayerData::setHaracze(int added_haracze){
    Haracze+=added_haracze;
    return Haracze;
}

int PlayerData::getBMW(){
    return BMW;
}

int PlayerData::setBMW(int added_bmw){
    BMW+=added_bmw;
    return BMW;
}
