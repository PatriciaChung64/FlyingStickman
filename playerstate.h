#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

class Stage3Player;
//base player state class, i.e. size = "normal"
//define standard collision effect on stickman,
//could be overridden by other state subclasses to simulate different effects

class PlayerState {
public:
    PlayerState(Stage3Player *player);

    virtual void leftCollisionEffect(Stage3Player *player);
    virtual void rightCollisionEffect(Stage3Player *player);
    virtual void topCollisionEffect(Stage3Player *player);
    virtual void bottomCollisionEffect(Stage3Player *player);

    virtual ~PlayerState();
};

#endif // PLAYERSTATE_H
