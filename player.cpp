#include <allegro.h>
#include "player.h"
#include "object.h"
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
