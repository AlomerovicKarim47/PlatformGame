#include "object.h"
#include <string>

#ifndef SLIME_H
#define SLIME_H

class Slime : public Object {
    public:
        std::string state = "ball";
        std::string previousState = "ball";
        float ySpeed = 1;
        float xSpeed = 0;
        float previousXSpeed = 0;
        
        void update() override;
        
    private:
};
#endif
