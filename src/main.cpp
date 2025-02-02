#include "game.h"
#include "utils/logger.h"

int main() {
    try {
        Game game;
        game.run();
    } catch (const std::exception& e) {
        Logger::err("{}", e.what());
        return -1;
    }

    return 0;
}