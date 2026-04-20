#include <vector>
#include <allegro.h>
#include "object.h"
#include "camera.h"

#ifndef GAME_H
#define GAME_H

class Game{

public:
    BITMAP* bmp;
    BITMAP* background;
    Camera* camera;
    std::vector<Object*>* objects;
    void init();
    void update();
    void draw();
    void end();
    void loadMap();
};

#endif
