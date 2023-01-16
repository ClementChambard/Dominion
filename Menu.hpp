#ifndef MENU_H_
#define MENU_H_

#include "VertexBatch.hpp"
#include "Button.hpp"

class App;

class Menu {
    public:
        Menu(App* app) : m_app(app) {}
        ~Menu() = default;

        void on_tick();
        void on_render(VertexBatch* batch);
        void on_renderUI(VertexBatch* batch);

    private:
        App* m_app;
        // buttons : New Game   Load Game   Online ?   Settings ?   Quit
        Button btn_NewGame{{247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{0.0f,0.3f},{0.3f,0.2f}};
        Button btn_LoadGame{{247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{0.0f,0.0f},{0.3f,0.2f}};
        Button btn_Quit{{247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{0.0f,-0.3f},{0.3f,0.2f}};
};

#endif // MENU_H_
