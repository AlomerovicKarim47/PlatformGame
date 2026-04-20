#include "slime_spawner.h"
#include "slime.h"
#include <vector>

void SlimeSpawner::update(){
    Object::update();
    if (state == "idle"){
        firstFrame = 0;
        lastFrame = 8;
        spawnTimer--;
    }
    if (state == "spawn"){
        firstFrame = 9;
        lastFrame = 23;
        if (currentSpriteFrame == lastFrame)
            state = "idle";
        else if (currentSpriteFrame == 16){
            slimeBall = new Slime();
            slimeBall->setLayer(layer);
            std::vector<const char*> slimeBallFrames = {
                "slime_ball.bmp",
                "slime_spawn2.bmp", "slime_spawn3.bmp", "slime_spawn4.bmp", "slime_spawn5.bmp", "slime_spawn6.bmp", 
                "slime_spawn7.bmp", "slime_spawn8.bmp", "slime_spawn9.bmp", "slime_spawn10.bmp",
                "slime_spawn11.bmp", "slime_spawn12.bmp", "slime_spawn13.bmp", "slime_spawn14.bmp", "slime_spawn15.bmp",
                "slime_move1.bmp", "slime_move2.bmp", "slime_move3.bmp", "slime_move4.bmp", "slime_move5.bmp",
                "slime_move6.bmp", "slime_move7.bmp", "slime_move8.bmp", "slime_move9.bmp", "slime_move10.bmp"
                };
            slimeBall->setSprite(slimeBallFrames);
            slimeBall->setMask("slime_ball_mask.bmp");
            slimeBall->x = x + 4;
            slimeBall->y = y + 32;
            slimeBall->otherObjects = otherObjects;
            otherObjects->push_back(slimeBall);
        }
    }
    if (spawnTimer < 0 && (!slimeBall || slimeBall->state == "dead") && currentSpriteFrame == firstFrame){ // making also sure the animation doesn't do weird skips uppon state change
        spawnTimer = 30 * 5;   
        state = "spawn";
    }
}
