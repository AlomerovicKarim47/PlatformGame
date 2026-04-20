#include "camera.h"
#include "object.h"

Camera::Camera(int w, int h){
    this->w = w;    
    this->h = h;
    x = 0;
    y = 0;
}

void Camera::setLayer(BITMAP* bmp){
    layer = bmp;
}

void Camera::setFocus(Object* object){
    focus = object;
}

void Camera::update(){
    if (focus->x > w/2)
        x = focus->x - w/2;
    if (focus->y > h/2)
        y = focus->y - h/2;
        
    if (x + w >= layer->w)
        x = layer->w - w;
    if (y + h >= layer->h)
        y = layer->h - h;
}

void Camera::draw(){
    
    

}
