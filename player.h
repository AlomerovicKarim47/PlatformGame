#include "object.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player : public Object{
public:
    Player();
    void update() override; 
    float xSpeed = 0;
    float ySpeed = 0;

private:
    float walkSpeed = 3;
    float jumpSpeed = 10;
    float gravity = 1;
    float maxFallSpeed = 20;
    bool jumpReleased = true;
    bool bounceOffEnemy = false;
};

#endif
