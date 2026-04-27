#include <allegro.h>
#include "player.h"
#include "object.h"
#include "impact_effect.h"
#include "slime.h"
#include <iostream>
#include <cmath>

Player::Player(){
    type = "player";
}

void Player::update(){
    Object::update();
    
    firstFrame = 0;
    lastFrame = 5;
    
    if (key[KEY_D]){
        if (xSpeed < walkSpeed)
            xSpeed += 0.5;
        else{
            xSpeed = walkSpeed;
        }
        if (xSpeed > 0)
            spriteFlipX = 1;
    }
    else if (key[KEY_A]){
        if (xSpeed > -walkSpeed)
            xSpeed -= 0.5;
        else{
            xSpeed = -walkSpeed;
        }
        if (xSpeed < 0)
            spriteFlipX = -1;
    }
    else{
        if (xSpeed <= -0.2 || xSpeed >= 0.2)
            xSpeed -= xSpeed/std::abs(xSpeed) * 0.2;
        else
            xSpeed = 0;
    }
        
    if (placeMeeting(x + xSpeed, y, "collision_block")){
        if (xSpeed > 0){
            xSpeed = 0;
            while(!placeMeeting(x + 1, y, "collision_block"))
                x += 1;
        }
        else if (xSpeed < 0){
            xSpeed = 0;
            while(!placeMeeting(x - 1, y, "collision_block"))
                x -= 1;
        }
    }
    
    x += xSpeed;
    
    
    if (key[KEY_W]){
        if (jumpReleased && placeMeeting(x, y + 10, "collision_block"))
            ySpeed = -jumpSpeed;
        jumpReleased = false;
    }
     else if (!jumpReleased){ 
        if (ySpeed < 0) ySpeed = ySpeed/2;   
        jumpReleased = true;
    }
    
    if (bounceOffEnemy) {
        bounceOffEnemy = false;
        ySpeed = -jumpSpeed;
    }
    
    ySpeed += gravity;
    if (ySpeed > maxFallSpeed)
        ySpeed = maxFallSpeed;
    
    
    if (placeMeeting(x, y + ySpeed, "collision_block")){
        if (ySpeed > 0){
            ySpeed = 0;
            while (!placeMeeting(x, y + 1, "collision_block"))
                y += 1;    
        }
        else if (ySpeed < 0){
            ySpeed = 0;
            while (!placeMeeting(x, y - 1, "collision_block"))
                y -= 1;    
        }
    }
    
    if (placeMeeting(x, y + ySpeed, "slime") && ySpeed > 0){
        std::vector<Object*>* slimes = new std::vector<Object*>();
        ySpeed = 0;
        while (!placeMeeting(x, y + 1, "slime", slimes))
            y += 1;
        bounceOffEnemy = true;
        Object* impactEffect = new Object();
        std::vector<const char *> impactEffectFrames = {"impact_effect1.bmp", "impact_effect3.bmp", "impact_effect5.bmp"};
        impactEffect->setSprite(impactEffectFrames);
        impactEffect->setLayer(layer);
        impactEffect->x = x + 6;
        impactEffect->y = y + 16;
        impactEffect->otherObjects = otherObjects;
        impactEffect->destroyOnAnimationEnd = true;
        otherObjects->push_back(impactEffect);
        
        (*slimes)[0]->health -= 1;
        
        
        
        
    }    
    
    y += ySpeed;
    
    
    
    if (!placeMeeting(x, y + 1, "collision_block")){ 
        if (ySpeed < 0)
            currentSpriteFrame = 7;
        else
            currentSpriteFrame = 8;
    }
    else{
        if (xSpeed > -walkSpeed && xSpeed < walkSpeed) currentSpriteFrame = 3;
        if (xSpeed >= -1 && xSpeed <= 1) currentSpriteFrame = 6;
    }
}
