#include <allegro.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "game.h"
#include "object.h"
#include "player.h"
#include "camera.h"
#include "slime_spawner.h"

void Game::init(){
    objects = new std::vector<Object*>();
    
    background = load_bitmap("background_boulders1.bmp", NULL);
    bmp = create_bitmap(640, 480);
    
    camera = new Camera(320, 240);
    camera->setLayer(bmp);
    
    loadMap();
}

void Game::loadMap(){
    std::ifstream mapFile("map.txt");
    std::string mapLine;
    
    int newObjectX = 0;
    int newObjectY = 0;
    
    while (getline (mapFile, mapLine)){
        std::stringstream ss(mapLine);
        std::string objectType;
        newObjectX = 0;
        while (getline(ss, objectType, ',')){
            if (objectType == "1"){
                Object* newObject;
                newObject = new Player();
                std::vector<const char*> ballGuyFrames = {
                    "ball_guy1.bmp", 
                    "ball_guy2.bmp", 
                    "ball_guy3.bmp", 
                    "ball_guy4.bmp", 
                    "ball_guy5.bmp", 
                    "ball_guy6.bmp", 
                    "ball_guy_standing.bmp", 
                    "ball_guy_jump1.bmp", 
                    "ball_guy_jump2.bmp"};
                newObject->setLayer(bmp);
                newObject->setSprite(ballGuyFrames);
                std::vector<Mask> masks;
                Mask mask = {5, 0, 22, 32};
                masks.push_back(mask);
                newObject->setMask(masks);
                camera->setFocus(newObject);
                newObject->x = newObjectX * 32;
                newObject->y = newObjectY * 32;
                objects->push_back(newObject);
            }
            if (objectType == "2"){
                Object* newObject;
                newObject = new Object("collision_block");
                std::vector<const char*> blockMask = {"boulders_block.bmp"};
                newObject->setLayer(bmp);
                newObject->setSprite(blockMask);
                std::vector<Mask> masks;
                Mask mask = {0, 0, 32, 32};
                masks.push_back(mask);
                newObject->setMask(masks);
                newObject->x = newObjectX * 32;
                newObject->y = newObjectY * 32;
                objects->push_back(newObject);
            }     
            if (objectType == "3"){
                Object* newObject;
                newObject = new SlimeSpawner();
                std::vector<const char*> slimeSpawnerFrames = {                    
                    "slime_spawner1.bmp",
                    "slime_spawner2.bmp",
                    "slime_spawner3.bmp",
                    "slime_spawner4.bmp",
                    "slime_spawner5.bmp",
                    "slime_spawner6.bmp",
                    "slime_spawner7.bmp",
                    "slime_spawner8.bmp",
                    "slime_spawner9.bmp",
                    "slime_spawner_drop1.bmp",
                    "slime_spawner_drop2.bmp",
                    "slime_spawner_drop3.bmp",
                    "slime_spawner_drop4.bmp",
                    "slime_spawner_drop5.bmp",
                    "slime_spawner_drop6.bmp",
                    "slime_spawner_drop7.bmp",
                    "slime_spawner_drop11.bmp",
                    "slime_spawner_drop12.bmp",
                    "slime_spawner_drop13.bmp",
                    "slime_spawner_drop14.bmp",
                    "slime_spawner_drop15.bmp",
                };
                newObject->setLayer(bmp);
                newObject->setSprite(slimeSpawnerFrames);
                newObject->x = newObjectX * 32;
                newObject->y = newObjectY * 32;
                objects->push_back(newObject);
            } 
            newObjectX++;
        }
        newObjectY++;
    }
    
    mapFile.close();
    
    for (int i = 0; i < objects->size(); i++)
        (*objects)[i]->otherObjects = objects;
}

void Game::update(){
    poll_keyboard();
    for (int i = 0; i < objects->size(); i++){
        if ((*objects)[i]->active)
            (*objects)[i]->update();
        else{
            //delete (*objects)[i];
            //(*objects)[i] = NULL;
            objects->erase(std::remove(objects->begin(), objects->end(), (*objects)[i]), objects->end());
        }
    }
    camera->update();    
}

void Game::draw(){
    for (int i = 0; i < bmp->h / background->h; i++){
        for (int j = 0; j < bmp->w / background->w; j++)
            blit(background, bmp, 0, 0, j * background->w, i * background->h, background->w, background->h);
    }

    for (int i = 0; i < objects->size(); i++)
        if ((*objects)[i]->active)
            (*objects)[i]->draw();
    
    stretch_blit(bmp, screen, camera->x, camera->y, camera->w, camera->h, 0, 0, 640, 480);
    clear_bitmap(bmp);
}

void Game::end(){
    destroy_bitmap(bmp);    
    for (int i = 0; i < objects->size(); i++)
        delete (*objects)[i];
    delete objects;
    delete camera;
}
