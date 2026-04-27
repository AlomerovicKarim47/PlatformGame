#include "object.h"
#include <allegro.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include<iterator>

Object::Object(){
    layer = NULL;
    sprite = NULL;
    x = 0;
    y = 0;    
    animationSpeed = 3;
    animationClock = animationSpeed;
    currentSpriteFrame = 0;
    type = "generic";
    spriteFlipX = 1;
    firstFrame = 0;
    lastFrame = 0;
    health = 3;
}

Object::Object(std::string type) : Object(){
    this->type = type;
}

Object::~Object(){
    for (int i = 0; i < spriteFrames.size(); i++)
        destroy_bitmap(spriteFrames[i]);
    destroy_bitmap(layer);   
}

void Object::setSprite(std::vector<const char*> frames){
    for (int i = 0; i < frames.size(); i++){
        BITMAP* newFrame = load_bitmap(frames[i], NULL);
        spriteFrames.push_back(newFrame);
    }
    sprite = spriteFrames[0];
    lastFrame = spriteFrames.size() - 1;
}

void Object::setMask(std::vector<Mask> mask){
    this->mask = mask;
}

void Object::setLayer(BITMAP* bmp){
    layer = bmp;    
}

void Object::setAnimationSpeed(int speed){
    animationSpeed = speed;
}

void Object::draw(){
    sprite = spriteFrames[currentSpriteFrame];
    if (spriteFlipX < 0)
        draw_sprite_h_flip(layer, sprite, x, y);    
    else
        draw_sprite(layer, sprite, x, y);    
}

void Object::update(){
    animationClock--;
    if (animationClock <= 0){
        animationClock = animationSpeed;
        if (currentSpriteFrame < firstFrame)
            currentSpriteFrame = firstFrame;
        else
            currentSpriteFrame++;
        if (currentSpriteFrame > lastFrame){
            if (destroyOnAnimationEnd){
                active = false;
            }
            currentSpriteFrame = firstFrame;
        }
    }
}

bool Object::placeMeeting(float x, float y, std::string objectType, std::vector<Object*>* collidedObjects){
    std::vector<Object*> objectsOfType;
    std::copy_if(otherObjects->begin(), otherObjects->end(), std::back_inserter(objectsOfType), [objectType](Object* o) {return o->type == objectType;});
    
    bool collision = false;
        
    for (int i = 0; i < objectsOfType.size(); i++){
        
        Object* o = objectsOfType[i];
        
        for (int j = 0; j < mask.size(); j++){
            int maskX = mask[j].x;
            int maskY = mask[j].y;
            int maskW = mask[j].w;
            int maskH = mask[j].h;
            
            for (int k = 0; k < o->mask.size(); k++){
                Mask oMask = o->mask[k];
                int oX = o->x;
                int oY = o->y;
                int oMaskX = oMask.x;
                int oMaskY = oMask.y;
                int oMaskW = oMask.w;
                int oMaskH = oMask.h;
                
                if (x + maskX + maskW > oX + oMaskX && 
                    x + maskX < oX + oMaskX + oMaskW && 
                    y + maskY + maskH > oY + oMaskY && 
                    y + maskY < oY + oMaskH + oMaskX){
                        if (collidedObjects){
                            collidedObjects->push_back(o);
                        }
                        collision = true;
                        break;
                } 
            }
        }
    }
    return collision;
}
