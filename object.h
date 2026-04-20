#include <allegro.h>
#include <vector>
#include <string>

#ifndef OBJECT_H
#define OBJECT_H

class Object{
 
public:
    Object();
    Object(std::string type);
    ~Object();
    int x, y, w, h;
    int spriteFlipX;
    int currentSpriteFrame;
    std::string type;
    std::vector<Object*>* otherObjects;
    int maskX, maskY;
    int firstFrame;
    int lastFrame;
    BITMAP* layer;
    std::vector<BITMAP*> spriteFrames;
    
    void setSprite(std::vector<const char*> frames);
    void setMask(const char* mask, int maskX = 0, int maskY = 0);
    void setLayer(BITMAP* bmp);
    void setAnimationSpeed(int speed);
    void draw();
    virtual void update();
    bool placeMeeting(float x, float y, std::string objectType);
    
private:
    BITMAP* sprite;
    int animationSpeed;
    int animationClock;
};

#endif
