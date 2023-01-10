#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexBatch.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "CardsType/ActionSimple.hpp"
#include "Game.hpp"
#include "CardsType/Witch.hpp"
#include "CardsType/CouncilRoom.hpp"
#include "CardsType/Chancelor.hpp"
#include "CardsType/Feast.hpp"
#include "CardsType/Mine.hpp"
#include "CardsType/Moat.hpp"
#include "Card.hpp"
#include "CardPile.hpp"
#include "CardFan.hpp"
#include "CardBoard.hpp"
#include "Mouse.hpp"
#include "Button.hpp"

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 900;
const int WINDOW_FLAGS = SDL_WINDOW_OPENGL;

int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)  { std::cout << "Error: failed to initialize SDL.\n"; exit(1); }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow("Dominion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    if (window == nullptr) { std::cout << "Error: failed to create window.\n"; exit(1); }
    Mouse::setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) { std::cout << "Error: failed to create context.\n"; exit(1); }

    GLenum Error = glewInit();
    if (Error != GLEW_OK) { std::cout << "Error: failed to initialize glew.\n"; exit(1); }

    SDL_GL_SetSwapInterval(1);

    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);

    Shader* shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Texture* texture = new Texture("textures/st01a.png");
    Texture* textureBG = new Texture("textures/stage05a.png");
    Texture* textureCard = new Texture("textures/Carte.png");
    Texture* textButtons = new Texture("textures/buttons.png");
    
    VertexBatch* batch = new VertexBatch();

    GLuint projMatrixLocation = shader->getUniformLocation("projectionMatrix");
    GLuint viewMatrixLocation = shader->getUniformLocation("viewMatrix");

    glm::mat4 projection = glm::perspective(3.141592f/4.f, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 1000.f);
    glm::mat4 view = glm::lookAt(glm::vec3{0.f,-1.f,5.f}, glm::vec3{0.f,0.f,0.f}, glm::vec3{0.f,0.f,1.f});
    Mouse::setInvPV(glm::inverse(projection * view));
    Mouse::setCamPos(glm::vec3{0.f, -1.f, 5.f});


    // TODO: Menu to choose the cards
    Game game {2, {
        new ActionSimple(0,0,0,3,"Smithy",4,{4.f/7.f,0.f,5/7.f,0.2f}),
        new ActionSimple(2,0,0,1,"Village",3,{4.f/7.f,0.6f,5/7.f,0.8f}),
        new ActionSimple(1,0,0,2,"Laboratory",5,{3.f/7.f,0.4f,4/7.f,0.6f}),
        new ActionSimple(1,1,1,1,"Market",5,{1/7.f,0.6f,2/7.f,0.8f}),
        new Moat(),
        new ActionSimple(0,1,2,0,"Woodcutter",3,{5.f/7.f,0.8f,6/7.f,1.0f}),
        new Witch(),
        new CouncilRoom(),
        new Chancelor(),
        new Feast()
        

    }};


    // TEST
    CardFan testMain;
    testMain.setPos(Mouse::toWorld(WINDOW_WIDTH/2.f, WINDOW_HEIGHT, -0.5f));
    testMain.fixPos();

    CardPile testDeck {false};
    for (int i = 0; i < 17; i++) {
        testDeck.AddOnTop(new Card(game.getType(i)));
        testDeck.AddOnTop(new Card(game.getType(i)));
    }
    testDeck.setPos(Mouse::toWorld(130.f*WINDOW_WIDTH/1500.f, WINDOW_HEIGHT-150.f*WINDOW_HEIGHT/900.f, -1.5f));
    testDeck.fixPos();

    CardPile testDiscard {true};
    testDiscard.setPos(Mouse::toWorld(WINDOW_WIDTH-130.f*WINDOW_WIDTH/1500.f, WINDOW_HEIGHT-150.f*WINDOW_HEIGHT/900.f, -1.5f));
    testDiscard.fixPos();

    CardBoard testBoard;
    testBoard.setPos(Mouse::toWorld(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f+100.f, -1.f));
    testBoard.fixPos();

    Card* cardInMouse = nullptr;

    bool b = false;
    bool h = false;
    // END TEST


    bool running = true;
    SDL_Event event;
    while (running && !game.getEndGame()) {

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
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_o) {
                        if (h) testMain.highlightCard(Type::CardType::NONE);
                        else testMain.highlightCard(Type::CardType::ACTION);
                        h = !h;
                    }
                    if (event.key.keysym.sym == SDLK_u) {
                        if (!testMain.get(0)) break;
                        testBoard.Add(testMain.get(0));
                        testMain.remove(0);
                    }
                    if (event.key.keysym.sym == SDLK_i) {
                        while (testBoard.get(0))
                        {
                            testDiscard.AddOnTop(testBoard.get(0));
                            testBoard.remove(0);
                        }
                    }
                    if (event.key.keysym.sym == SDLK_h) {
                        if (!testMain.get(0)) break;
                        testDiscard.AddOnTop(testMain.get(0));
                        testMain.remove(0);
                    }
                    if (event.key.keysym.sym == SDLK_k) {
                        b = !b;
                    }
                    if (event.key.keysym.sym == SDLK_j) {
                        if (!testDeck.getOnTop()) {
                            testDeck.transmitFrom(testDiscard);
                            testDeck.shuffle();
                        }
                        if (!testDeck.getOnTop()) break;
                        testMain.Add(testDeck.getOnTop());
                        testDeck.removeOnTop();
                    }
                    if (event.key.keysym.sym == SDLK_l) {
                        if (cardInMouse) testDiscard.AddOnTop(cardInMouse);
                        if (!testDeck.getOnTop()) {
                            testDeck.transmitFrom(testDiscard);
                            testDeck.shuffle();
                        }
                        if (!testDeck.getOnTop()) break;
                        cardInMouse = testDeck.getOnTop();
                        testDeck.removeOnTop();
                    }
                    break;
                default:
                    break;
            }
            // other events
            Mouse::processEvent(event);
        }

        // Update
        if (cardInMouse) {
            cardInMouse->moveTo(Mouse::toWorldCurrent(0.25f));
            if (b) cardInMouse->rotateYTo(glm::pi<float>());
            else   cardInMouse->rotateYTo(0.f);
            cardInMouse->on_tick();
        }
        //testDeck.on_tick();
        //testDiscard.on_tick();
        //testMain.on_tick();
        //testBoard.on_tick();
        game.onTick();

        // Draw
        batch->clear_vertices(); // premiere etapes pour draw un rectangle
        shader->use();
        batch->draw_rectangle(0, 0, 0, 8, 6);  // deuxieme etape 
        batch->finish_adding(); // troisieme etape 

        shader->loadMat4(projMatrixLocation, projection);
        shader->loadMat4(viewMatrixLocation, view);

        batch->render(textureBG); // quatrieme etape
        batch->clear_vertices();

        // testDeck.on_render(batch);
        // testDiscard.on_render(batch);
        // testBoard.on_render(batch);
        // testMain.on_render(batch, true);
        game.onDraw(batch);
        // if (cardInMouse) cardInMouse->on_render(batch);
        

        batch->finish_adding();
        batch->render(textureCard);
        batch->clear_vertices();
        
        game.onRenderUI(batch);

        batch->finish_adding();

        shader->loadMat4(projMatrixLocation, glm::mat4(1.f));
        shader->loadMat4(viewMatrixLocation, glm::mat4(1.f));

        batch->render(textButtons);



        

        shader->unuse();

        SDL_GL_SwapWindow(window);
    }
    delete batch;
    delete texture;
    delete shader;
    delete textureBG;
    delete textureCard;
    if (cardInMouse) delete cardInMouse;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
