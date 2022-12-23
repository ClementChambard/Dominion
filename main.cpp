#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Shader.hpp"
#include "Texture.hpp"
#include "VertexBatch.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include "ActionSimple.hpp"
#include "Tresor.hpp"
#include "Victoire.hpp"
#include "Witch.hpp"
#include "CouncilRoom.hpp"
#include "Chancelor.hpp"
#include "Feast.hpp"
#include "Mine.hpp"
#include "Card.hpp"
#include "CardPile.hpp"
#include "CardFan.hpp"
#include "Mouse.hpp"

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
    glCullFace(GL_BACK);

    Shader* shader = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Texture* texture = new Texture("textures/st01a.png");
    Texture* textureBG = new Texture("textures/stage05a.png");
    Texture* textureCard = new Texture("textures/Carte.png");

    VertexBatch* batch = new VertexBatch();

    GLuint projMatrixLocation = shader->getUniformLocation("projectionMatrix");
    GLuint viewMatrixLocation = shader->getUniformLocation("viewMatrix");

    glm::mat4 projection = glm::perspective(3.141592f/4.f, (float)WINDOW_WIDTH/(float)WINDOW_HEIGHT, 0.01f, 1000.f);
    glm::mat4 view = glm::lookAt(glm::vec3{0.f,-1.f,5.f}, glm::vec3{0.f,0.f,0.f}, glm::vec3{0.f,0.f,1.f});
    glm::mat4 inv_p_v = glm::inverse(projection * view);

    shader->use();

    shader->loadMat4(projMatrixLocation, projection);
    shader->loadMat4(viewMatrixLocation, view);

    shader->unuse();

    ActionSimple Smithy = ActionSimple(0,0,0,3,"Smithy",4,{4.f/7.f,0.f,5/7.f,0.2f});
    ActionSimple Village = ActionSimple(2,0,0,1,"Village",3,{4.f/7.f,0.6f,5/7.f,0.8f});//uv faux
    ActionSimple Laboratory = ActionSimple(1,0,0,2,"Laboratory",5,{3.f/7.f,0.4f,4/7.f,0.6f});
    ActionSimple Market = ActionSimple(1,1,1,1,"Market",5,{1/7.f,0.6f,2/7.f,0.8f});
    ActionSimple Festival = ActionSimple(2,1,2,0,"Festival",5,{2.f/7.f,0.4f,3/7.f,0.6f});
    ActionSimple Woodcutter = ActionSimple(0,1,2,0,"Woodcutter",3,{5.f/7.f,0.8f,6/7.f,1.0f});

    Witch witch = Witch();
    CouncilRoom councilRoom = CouncilRoom();
    Chancelor chancelor =Chancelor();
    Feast feast = Feast();
    Mine mine = Mine();

    Tresor Copper = Tresor(1,"Copper",0,{2/7.f,0.f,3/7.f,0.2f});
    Tresor Silver = Tresor(2,"Silver",3,{1/7.f,0.f,2/7.f,0.2f});
    Tresor Gold = Tresor(3,"Gold",6,{1/7.f,0.4f,2/7.f,0.6f});

    Victoire Estate = Victoire(1,"Estate",2,{0.f,0.4f,1/7.f,0.6f});
    Victoire Duchy = Victoire(2,"Duchy",5,{4/7.f,0.2f,5/7.f,0.4f});
    Victoire Province = Victoire(3,"Province",8,{3/7.f,0.2f,4/7.f,0.4f});
    Victoire Curse = Victoire(-1,"Curse",0,{2/7.f,0.2f,3/7.f,0.4f});

    Card estateCard {&Estate};
    Card goldCard {&Gold};
    Card villageCard {&Village};
    Card marketCard {&Market};

    CardFan testMain;
    testMain.Add(new Card(&Estate));
    testMain.Add(new Card(&Gold));
    testMain.Add(new Card(&Village));
    testMain.Add(new Card(&Market));
    testMain.setPos(Mouse::toWorld(WINDOW_WIDTH/2.f, WINDOW_HEIGHT, 0.5, inv_p_v, glm::vec3{0.f,-1.f,5.f}));
    testMain.fixPos();

    CardPile testDeck {false};
    for (int i = 0; i < 10; i++) {
        testDeck.AddOnTop(new Card(&witch));
        testDeck.AddOnTop(new Card(&Estate));
        testDeck.AddOnTop(new Card(&Village));
    }
    testDeck.fixPos();

    CardPile testDiscard {true};
    testDiscard.setPos({2.f, 0.f, 0.f});
    testDiscard.fixPos();

    Card* cardInMouse = new Card(&witch);

    bool running = true;
    SDL_Event event;
    bool b = false;
    while (running) {

        glClearColor(0.3f, 0.6f, 0.1f, 1.f);
        glClearDepth(1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
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
            cardInMouse->moveTo(Mouse::toWorldCurrent(0, inv_p_v, glm::vec3{0.f,-1.f,5.f})+glm::vec3(0,0,0.25f));
            if (b) cardInMouse->rotateYTo(glm::pi<float>());
            else   cardInMouse->rotateYTo(0.f);
            cardInMouse->on_tick();
        }
        testDeck.on_tick();
        testDiscard.on_tick();
        testMain.on_tick();

        // Draw
        batch->clear_vertices();
        shader->use();
        batch->draw_rectangle(0, 0, 0, 8, 6);
        batch->finish_adding();
        batch->render(textureBG);
        batch->clear_vertices();

        testDeck.on_render(batch);
        testDiscard.on_render(batch);
        testMain.on_render(batch, true);
        if (cardInMouse) cardInMouse->on_render(batch);

        batch->finish_adding();
        batch->render(textureCard);
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
