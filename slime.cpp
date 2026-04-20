#include "slime.h"
#include <iostream>

void Slime :: update(){
    Object::update();
    
    if (state == "ball"){
        lastFrame = 0;
        ySpeed += 1;
        
        if (ySpeed > 20) 
            ySpeed = 20;
        
        if (placeMeeting(x, y + ySpeed, "collision_block")){
            ySpeed = 0;
            while (!placeMeeting(x, y + 1, "collision_block"))
                y += 1;
            previousState = state;
            state = "spawn";    
            y -= 16;
            x -= 28;
            currentSpriteFrame = 1; // manual override of animation loop to skip repositioned ball due to image size blah blah
            firstFrame = 1;
            lastFrame = 14;
        }
    }
    else if (state == "spawn"){
        if (currentSpriteFrame == 14){
            previousState = state;
            state = "moving";
        }
    }
    else if (state == "moving"){
        if (previousState == "spawn"){ 
            xSpeed = -2;
            setMask("slime_mask.bmp", 19, 28);
        }
        if (xSpeed == 0)
            xSpeed = -previousXSpeed;;
        if (xSpeed < 0){
            firstFrame = 15;
            lastFrame = 18;
        }
        if (xSpeed > 0){
            firstFrame = 20;
            lastFrame = 23;
        }
        if (placeMeeting(x + xSpeed, y, "collision_block")){
            previousXSpeed = xSpeed;
            xSpeed = 0;
            previousState = state;
            state = "direction_change";
        }
    }
    else if (state == "direction_change" && xSpeed == 0){ // if hasnt started moving in new direction
        if (previousXSpeed < 0){ // turnaround frame(s) based on direction it came from
            firstFrame = 19;
            lastFrame = 19;
        }
        else if (previousXSpeed > 0){
            firstFrame = 24;
            lastFrame = 24;
        }
        if (currentSpriteFrame == 19 || currentSpriteFrame == 24){
            previousState = state;
            state = "moving";
        }
    }
    
    x += xSpeed;
    y += ySpeed;
}
