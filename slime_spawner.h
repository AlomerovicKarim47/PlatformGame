#include <string>
#include "object.h"
#include "slime.h"

class SlimeSpawner : public Object{

public:
    void update() override;
    
private:     
    int spawnTimer = 30 * 5;
    std::string state = "idle";
    Slime* slimeBall = NULL;
};
