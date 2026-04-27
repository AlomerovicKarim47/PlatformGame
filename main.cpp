#include <allegro.h>
#include <vector>
#include "object.h"
#include "camera.h"
#include "player.h"
#include "game.h"

volatile long int coreClock = 0;

void incrementCoreClock(){
    ++coreClock;
}
END_OF_FUNCTION(incrementCoreClock)

int main(){
    allegro_init();
    install_keyboard();
    install_timer();
    LOCK_VARIABLE(coreClock);
    LOCK_FUNCTION(incrementCoreClock);
    install_int_ex(incrementCoreClock, BPS_TO_TIMER(30));
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);
    
    Game* game = new Game();
    game->init();
      
    while(!key[KEY_ESC]){
        while (coreClock > 0){
            int oldTicks = coreClock;

            game->update();

            --coreClock;

            if (oldTicks <= coreClock)
                break;              
        }
        game->draw();
    }
    game->end();
    return 0;
}
END_OF_MAIN()
