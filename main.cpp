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

const int WINDOW_WIDTH = 1500;
const int WINDOW_HEIGHT = 900;
const int WINDOW_FLAGS = SDL_WINDOW_OPENGL;

glm::vec2 mouseToWorld(float x, float y, float h, glm::mat4 const& inv_p_v, glm::vec3 C)
{
    glm::vec4 near = glm::vec4((x - WINDOW_WIDTH/2.f) / (WINDOW_WIDTH/2.f), -1*(y - WINDOW_HEIGHT/2.f) / (WINDOW_HEIGHT/2.f), -1, 1.0);
    glm::vec4 far = glm::vec4((x - WINDOW_WIDTH/2.f) / (WINDOW_WIDTH/2.f), -1*(y - WINDOW_HEIGHT/2.f) / (WINDOW_HEIGHT/2.f), 1, 1.0);
    glm::vec4 nearResult = inv_p_v*near;
    glm::vec4 farResult = inv_p_v*far;
    nearResult /= nearResult.w;
    farResult /= farResult.w;
    glm::vec3 T = C + glm::vec3(farResult - nearResult );
    if (C.z == T.z) return C;
    x = C.x - (T.x-C.x)*(C.z-h)/(T.z-C.z);
    y = C.y - (T.y-C.y)*(C.z-h)/(T.z-C.z);
    return {x, y};
}

void draw_rectangle(float x, float y, float z, float w, float h, VertexBatch* batch, glm::mat4 const& transf = glm::mat4(1.f))
{
    static const float hw = 0.4f;
    static const float hh = 0.5f;
    if (w <= 0) w = hw*2;
    if (h <= 0) h = hh*2;
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{-w/2,-h/2, 0, 1.f}, {255, 255, 255, 255}, {0, 1}});
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{+w/2,-h/2, 0, 1.f}, {255, 255, 255, 255}, {1, 1}});
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{+w/2,+h/2, 0, 1.f}, {255, 255, 255, 255}, {1, 0}});
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{-w/2,-h/2, 0, 1.f}, {255, 255, 255, 255}, {0, 1}});
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{+w/2,+h/2, 0, 1.f}, {255, 255, 255, 255}, {1, 0}});
    batch->add_vertex({glm::vec4(x,y,z,0) + transf * glm::vec4{-w/2,+h/2, 0, 1.f}, {255, 255, 255, 255}, {0, 0}});
}

int main() {

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) != 0)  { std::cout << "Error: failed to initialize SDL.\n"; exit(1); }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window* window = SDL_CreateWindow("Dominion", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_FLAGS);
    if (window == nullptr) { std::cout << "Error: failed to create window.\n"; exit(1); }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == nullptr) { std::cout << "Error: failed to create context.\n"; exit(1); }

    GLenum Error = glewInit();
    if (Error != GLEW_OK) { std::cout << "Error: failed to initialize glew.\n"; exit(1); }

    SDL_GL_SetSwapInterval(1);

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

    Tresor Copper = Tresor(1,"Copper",0,{2/7.f,0.f,3/7.f,0.2f});
    Tresor Silver = Tresor(2,"Silver",3,{1/7.f,0.f,2/7.f,0.2f});
    Tresor Gold = Tresor(3,"Gold",6,{1/7.f,0.4f,2/7.f,0.6f});
    Victoire Estate = Victoire(1,"Estate",2,{0.f,0.4f,1/7.f,0.6f});
    Victoire Duchy = Victoire(2,"Duchy",5,{4/7.f,0.2f,5/7.f,0.4f});
    Victoire Province = Victoire(3,"Province",8,{3/7.f,0.2f,4/7.f,0.4f});
    Victoire Curse = Victoire(-1,"Curse",0,{2/7.f,0.2f,3/7.f,0.4f});

    float x = 0.f, y = 0.f, z = 0.f, t = 0.f;
    bool running = true;
    SDL_Event event;
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
                case SDL_MOUSEMOTION:
                    x = event.motion.x;
                    y = event.motion.y;
                default:
                    break;
            }
            // other events
        }
        batch->clear_vertices();
        shader->use();

        draw_rectangle(0, 0, 0, 8, 6, batch);
        batch->finish_adding();
        batch->render(textureBG);
        glm::vec2 mwp = mouseToWorld(x, y, 0, inv_p_v, glm::vec3{0.f,-1.f,5.f});
        batch->clear_vertices();
        draw_rectangle(mwp.x, mwp.y, z+0.25f, 0, 0, batch, glm::rotate(glm::mat4(1.f), sin(t/2)/4, glm::vec3(0,0,1)));
        mwp = mouseToWorld(WINDOW_WIDTH/2.f, WINDOW_HEIGHT, 0.5, inv_p_v, glm::vec3{0.f,-1.f,5.f});
        draw_rectangle(mwp.x-0.9, mwp.y+0.3, 0.5f, 0, 0, batch, glm::rotate(glm::mat4(1.f), 0.45f, glm::vec3(0,0,1)));
        draw_rectangle(mwp.x-0.3, mwp.y+0.5, 0.5f, 0, 0, batch, glm::rotate(glm::mat4(1.f), 0.15f, glm::vec3(0,0,1)));
        draw_rectangle(mwp.x+0.3, mwp.y+0.5, 0.5f, 0, 0, batch, glm::rotate(glm::mat4(1.f), -0.15f, glm::vec3(0,0,1)));
        draw_rectangle(mwp.x+0.9, mwp.y+0.3, 0.5f, 0, 0, batch, glm::rotate(glm::mat4(1.f), -0.45f, glm::vec3(0,0,1)));

        batch->finish_adding();

        
        batch->render(texture);
        shader->unuse();

        SDL_GL_SwapWindow(window);

        t+=0.1f;
        z = cos(t)/4;
    }
    delete batch;
    delete texture;
    delete shader;
    delete textureBG;
    delete textureCard;
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    

    

    




    



    return 0;
}
