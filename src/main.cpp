#include "game.h"

int main(void) {
    Game game;
    game.initialize();
    game.loop();
    game.stop();
    return 0;
}
