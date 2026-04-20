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

void Object::setMask(const char *mask, int maskX, int maskY){
    BITMAP* maskBmp = load_bitmap(mask, NULL);
    this->maskX = maskX;
    this->maskY = maskY;
    w = maskBmp->w;
    h = maskBmp->h;    
    destroy_bitmap(maskBmp);
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
        if (currentSpriteFrame > lastFrame)
            currentSpriteFrame = firstFrame;
    }
}

bool Object::placeMeeting(float x, float y, std::string objectType){
    std::vector<Object*> objectsOfType;
    std::copy_if(otherObjects->begin(), otherObjects->end(), std::back_inserter(objectsOfType), [objectType](Object* o) {return o->type == objectType;});
    
    for (int i = 0; i < objectsOfType.size(); i++){
        Object* o = objectsOfType[i];
        if (x + maskX + w > o->x + o->maskX && x + maskX < o->x + o->maskX + o->w && y + h > o->y && y < o->y + o->h)
            return true;
    }
    
    return false;
}
