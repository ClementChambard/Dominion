#ifndef APP_H_
#define APP_H_

#include <SDL2/SDL.h>
#include "Texture.hpp"
#include "VertexBatch.hpp"
#include "SpriteFont.hpp"
#include "Game.hpp"
#include "Menu.hpp"

class App {

    public:
        App();
        ~App();

        void run();

        Game* initGame(int nbPlayer, std::array<int, 10> actionCardTypes) { return game = new Game(nbPlayer, actionCardTypes); }
        void close() { running = false; }
    private:
        bool running = true;

        SDL_Window* window;
        SDL_GLContext context;

        Texture* tex_cards;
        Texture* tex_background;
        Texture* tex_ui;

        Shader* shader;
        GLuint projMatrixLocation;
        GLuint viewMatrixLocation;

        glm::mat4 projection;
        glm::mat4 view;

        VertexBatch* batch;
        SpriteFont* spriteFont;

        Game* game;
        Menu menu{this};
};

#endif // APP_H_
