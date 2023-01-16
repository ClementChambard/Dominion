#include "Menu.hpp"
#include "SpriteFont.hpp"
#include "Mouse.hpp"
#include "App.hpp"

void Menu::on_tick()
{
    if (btn_NewGame .isHovered() && Mouse::press()) m_app->initGame(2, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9});
    if (btn_LoadGame.isHovered() && Mouse::press()) m_app->initGame(2, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9})->loadGame();
    if (btn_Quit    .isHovered() && Mouse::press()) m_app->close();
}

void Menu::on_render(VertexBatch*)
{

}

void Menu::on_renderUI(VertexBatch* batch)
{
    btn_LoadGame.onUpdate(batch);
    SpriteFont::last_created_instance->renderText("Load game", btn_LoadGame.getPos(), {0.5f, 0.5f});
    btn_NewGame.onUpdate(batch);
    SpriteFont::last_created_instance->renderText("New game", btn_NewGame.getPos(), {0.5f, 0.5f});
    btn_Quit.onUpdate(batch);
    SpriteFont::last_created_instance->renderText("Quit", btn_Quit.getPos(), {0.5f, 0.5f});
}
