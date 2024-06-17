#ifndef NOTHREADSEVENTPACKTM_H
#define NOTHREADSEVENTPACKTM_H

class PlayerClient;

enum class TypeUpdate{
    Szacun,
    Name
};

class NoThreadsEventPackTM
{
public:
    NoThreadsEventPackTM();
    void addListenerAgent(PlayerClient* sledz);
    void Notify(TypeUpdate update);
private:
    PlayerClient* sledz;
};

#endif // NOTHREADSEVENTPACKTM_H
