#include "App.hpp"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Mouse.hpp"
#include "CardsType/GameCards.hpp"

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 900;
const int WINDOW_FLAGS = SDL_WINDOW_OPENGL;

App::App() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)  { std::cout << "Error: failed to initialize SDL.\n"; exit(1); }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow("Dominion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    if (window == nullptr) { std::cout << "Error: failed to create window.\n"; exit(1); }
    Mouse::setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    context = SDL_GL_CreateContext(window);
    if (context == nullptr) { std::cout << "Error: failed to create context.\n"; exit(1); }

    GLenum Error = glewInit();
    if (Error != GLEW_OK) { std::cout << "Error: failed to initialize glew.\n"; exit(1); }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);

    shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    tex_background = new Texture("textures/stage05a.png");
    tex_cards = new Texture("textures/Carte.png");
    tex_ui = new Texture("textures/buttons.png");

    batch = new VertexBatch();
    spriteFont = new SpriteFont("font.fnt");

    projMatrixLocation = shader->getUniformLocation("projectionMatrix");
    viewMatrixLocation = shader->getUniformLocation("viewMatrix");

    projection = glm::perspective(3.141592f/4.f, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 1000.f);
    view = glm::lookAt(glm::vec3{0.f,-1.f,5.f}, glm::vec3{0.f,0.f,0.f}, glm::vec3{0.f,0.f,1.f});
    Mouse::setInvPV(glm::inverse(projection * view));
    Mouse::setCamPos(glm::vec3{0.f, -1.f, 5.f});

    GameCards::InitGameCardsTypes();

    game = nullptr;
}

App::~App() {

    if (game) delete game;

    GameCards::CleanupGameCardsTypes();

    delete spriteFont;
    delete batch;
    delete tex_ui;
    delete tex_cards;
    delete tex_background;
    delete shader;

    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void App::run() {
    bool pressedCtrol = false;
    SDL_Event event;

    while (running && (!game || !game->getEndGame())) {

        glClearColor(0.3f, 0.6f, 0.1f, 1.f);
        glClearDepth(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Mouse::resetState();
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYUP:
                    if (event.key.keysym.sym == SDLK_LCTRL) pressedCtrol = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_l && pressedCtrol) {
                        game->loadGame();
                    }
                    if (event.key.keysym.sym == SDLK_LCTRL) {
                        pressedCtrol = true;
                    }
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        if (game) delete game;
                        game = nullptr;
                    }
                    break;
                default:
                    break;
            }
            // other events
            Mouse::processEvent(event);
        }

        // Update
        if (game) game->onTick();
        else menu.on_tick();

        // Draw
        shader->use();
            shader->loadMat4(projMatrixLocation, projection);
            shader->loadMat4(viewMatrixLocation, view);

                batch->draw_rectangle(0, 0, 0, 8, 6);

            batch->finish_adding();
            batch->render(tex_background);
            batch->clear_vertices();

                if (game) game->onDraw(batch);
                else menu.on_render(batch);

            batch->finish_adding();
            batch->render(tex_cards);
            batch->clear_vertices();

            shader->loadMat4(projMatrixLocation, glm::mat4(1.f));
            shader->loadMat4(viewMatrixLocation, glm::mat4(1.f));

                if (game) game->onRenderUI(batch);
                else menu.on_renderUI(batch);

            batch->finish_adding();
            batch->render(tex_ui);
            batch->clear_vertices();

                spriteFont->renderAllText();

        shader->unuse();

        SDL_GL_SwapWindow(window);
    }
}
