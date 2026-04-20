#pragma once
#include <allegro.h>
#include "object.h"

class Camera{

public:
    int x, y;
    int w, h;
    
    Camera(int w, int h);
    
    void setLayer(BITMAP* bmp);
    void setFocus(Object* object);
    void update();
    void draw();
    
private:
    BITMAP* layer;
    Object* focus;
};
