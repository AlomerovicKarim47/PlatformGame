#include <allegro.h>
#include <vector>
#include <string>

#ifndef OBJECT_H
#define OBJECT_H

struct Mask{
    int x, y, w, h;
};

class Object{
 
public:
    Object();
    Object(std::string type);
    ~Object();
    int x, y;
    int spriteFlipX;
    int currentSpriteFrame;
    std::string type;
    int health;
    std::vector<Object*>* otherObjects;
    std::vector<Mask> mask;
    int firstFrame;
    int lastFrame;
    BITMAP* layer;
    std::vector<BITMAP*> spriteFrames;
    std::vector<Mask> maskList;
    
    bool destroyOnAnimationEnd = false;
    bool active = true;
    
    
    void setSprite(std::vector<const char*> frames);
    void setMask(std::vector<Mask> mask);
    void setLayer(BITMAP* bmp);
    void setAnimationSpeed(int speed);
    void draw();
    virtual void update();
    bool placeMeeting(float x, float y, std::string objectType, std::vector<Object*>* collidedObjects = NULL);
    
private:
    BITMAP* sprite;
    int animationSpeed;
    int animationClock;
};

#endif
