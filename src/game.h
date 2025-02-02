#pragma once

#include <SDL3/SDL.h>

class Game {
public:
    Game();
    ~Game();

    void run();
private:
    SDL_Window* m_window { nullptr };
    SDL_GLContext m_context;

    SDL_Event m_event;

    bool m_quit { false };

    void init();
    void update();
    void handleEvents();
    void draw();
    void close();
};