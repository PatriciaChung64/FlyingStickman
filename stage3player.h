#ifndef STAGE3PLAYER_H
#define STAGE3PLAYER_H

#include <memory>

#include "stickman.h"
#include "coordinate.h"
#include "entity.h"
#include "playerstate.h"
#include "gameobserver.h"

//stage 3 player handles checking its own collision with the current list of obstacles
//also manages its own x, y velocity when jumping/colliding

class StageMemento;

class Stage3Player : public Stickman {
    friend class StageMemento;
    friend class Stage3Tester;
public:
    explicit Stage3Player(int lives, std::shared_ptr<GameObserver> gameObserver);

    bool checkGoalCollision(Entity *goal);
    bool checkTopCollision(std::vector<Entity *>obstacles);
    bool checkBottomCollision(std::vector<Entity *>obstacles);
    bool checkLeftCollision(std::vector<Entity *>obstacles);
    bool checkRightCollision(std::vector<Entity *>obstacles);

    void applyTopCollisionEffect();
    void applyBottomCollisionEffect();
    void applyLeftCollisionEffect();
    void applyRightCollisionEffect();

    int getLives();
    double getYVelocity() { return yVelocity; }
    double getYPosition() { return position->getYCoordinate(); }
    double getXPosition() { return position->getXCoordinate(); }
    int getJumpHeight() { return jumpHeight; }
    bool getReachedGoal() { return reached_Goal; }
    bool getJumping() { return jumping; }
    bool getFalling() { return falling; }
    bool getResetStage() { return reset_Stage; }
    int getCurrency() { return currency; }
    std::shared_ptr<GameObserver> getGameObserver() { return gameObserver; }

    void decreaseLives();
    void changeYVelocity(double new_velocity) { yVelocity += new_velocity; }
    void updateXPosition(double offset) { position->changeInXCoordinate(offset); }
    void updateYPosition(double offset) { position->changeInYCoordinate(offset); }
    void setYVelocity(double new_velocity) { yVelocity = new_velocity; }
    void setJumpHeight(int new_height) { jumpHeight = new_height; }
    void setMaxJumpCount(int new_max) { max_jump_count = new_max; }
    void setJumping(bool state) { jumping = state; }
    void setFalling(bool state) { falling = state; }
    void setDestroyOnCollision(bool state) { destroy_On_Collision = state; }
    void setReachedGoal(bool state) { reached_Goal = state; }
    void setResetStage(bool state) { reset_Stage = state; }
    void setJumpCount(int new_count) { jump_count = new_count; }
    void incrementCurrency() { currency++; }
    void setCurrency(int new_currency) { currency = new_currency; }

    virtual void updateStickman() override;

    virtual void jump();
    virtual void update(bool paused, double time_since_last_frame, std::vector<Entity *>obstacles);
    virtual void render(QPainter &painter);

    Stage3Player *makeMemento() { return this; }
    void restoreState(std::shared_ptr<Stage3Player> playerMemento);

protected:
    int lives;
    int currency;
    double yVelocity;
    bool destroy_On_Collision;
    std::unique_ptr<Coordinate> position;
    std::unique_ptr<PlayerState> currentState;

    std::shared_ptr<GameObserver> gameObserver;

    bool reached_Goal;
    bool reset_Stage;

    int animation_update_counter;
    int frame_number;

    int jumpHeight;
    int max_jump_count;
    int jump_count;

    bool jumping;
    bool falling;

    double gravity;
};

#endif // STAGE3PLAYER_H
