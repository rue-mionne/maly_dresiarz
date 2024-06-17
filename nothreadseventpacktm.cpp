#include "nothreadseventpacktm.h"
#include "playerclient.h"

NoThreadsEventPackTM::NoThreadsEventPackTM() {}

void NoThreadsEventPackTM::addListenerAgent(PlayerClient *sledz){
    this->sledz=sledz;
}

void NoThreadsEventPackTM::Notify(TypeUpdate update){
    sledz->statsChange(update);
}
