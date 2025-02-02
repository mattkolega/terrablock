#include "game.h"

#include <cstdint>
#include <stdexcept>
#include <string>

#include <glad/glad.h>

#include "utils/logger.h"

static constexpr int SCREEN_WIDTH { 1280 };
static constexpr int SCREEN_HEIGHT { 720 };

Game::Game() {
    init();
}

Game::~Game() {
    close();
}

void Game::run() {
    while (!m_quit) {
        update();
        draw();
    }
}

void Game::init() {
    if(!SDL_Init(SDL_INIT_VIDEO)) {
        throw std::runtime_error("SDL could not be initialised! SDL_Error: " + std::string(SDL_GetError()));
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    uint64_t windowFlags = SDL_WINDOW_OPENGL;
    m_window = SDL_CreateWindow("Terrablock", SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags);
    if (m_window == nullptr) {
        throw std::runtime_error("SDL window could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }

    m_context = SDL_GL_CreateContext(m_window);
    if (m_context == nullptr) {
        throw std::runtime_error("SDL OpenGL context could not be created! SDL_Error: " + std::string(SDL_GetError()));
    }
    SDL_GL_MakeCurrent(m_window, m_context);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        throw std::runtime_error("Failed to initialise GLAD");
    }

    Logger::info("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
    Logger::info("OpenGL Shading Language Version: {}", reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));
    Logger::info("OpenGL Vendor: {}", reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
    Logger::info("OpenGL Renderer: {}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));

    glClearColor(0.4f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(m_window);
}

void Game::update() {
    handleEvents();
}

void Game::handleEvents() {
    while (SDL_PollEvent(&m_event)) {
        switch (m_event.type) {
            case SDL_EVENT_KEY_DOWN:
                switch (m_event.key.key) {
                    case SDL_SCANCODE_ESCAPE:
                        m_quit = true;
                        break;
                }
                break;
            case SDL_EVENT_QUIT:
                m_quit = true;
                break;
        }
	}
}

void Game::draw() {
    glClearColor(0.4f, 0.85f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    SDL_GL_SwapWindow(m_window);
}

void Game::close() {
    SDL_GL_DestroyContext(m_context);

    SDL_DestroyWindow(m_window);
    m_window = nullptr;

    SDL_Quit();
}