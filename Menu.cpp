#include "Menu.hpp"
#include "SpriteFont.hpp"
#include "Mouse.hpp"
#include "App.hpp"
#include "CardsType/GameCards.hpp"

void Menu::on_tick()
{
    switch (submenu) {
        case Submenu::MAIN:
            if (btn_NewGame .isHovered() && Mouse::press()) submenu = Submenu::PLAYERCOUNT;
            if (btn_LoadGame.isHovered() && Mouse::press()) submenu = Submenu::SAVESELECT;
            if (btn_Quit    .isHovered() && Mouse::press()) m_app->close();
            break;
        case Submenu::PLAYERCOUNT:
            if (btn_2Pl .isHovered() && Mouse::press()) { playerCount = 2; submenu = Submenu::CARDSELECT; }
            if (btn_3Pl .isHovered() && Mouse::press()) { playerCount = 3; submenu = Submenu::CARDSELECT; }
            if (btn_4Pl .isHovered() && Mouse::press()) { playerCount = 4; submenu = Submenu::CARDSELECT; }
            if (btn_Quit.isHovered() && Mouse::press()) submenu = Submenu::MAIN;
            break;
        case Submenu::CARDSELECT: {
            if (btn_Quit.isHovered() && Mouse::press()) submenu = Submenu::PLAYERCOUNT;
            if (btn_Confirm.isHovered() && Mouse::press() && cardTypes.size() == 10) {
                submenu = Submenu::MAIN;
                m_app->initGame(playerCount, {cardTypes[0], cardTypes[1], cardTypes[2], cardTypes[3], cardTypes[4], cardTypes[5], cardTypes[6], cardTypes[7], cardTypes[8], cardTypes[9]});
            }
            // TODO: UPDATE CARD SELECTION
            glm::vec2 mpos = Mouse::toWorldCurrent(-5);
            for (int i = 0; i < 25; i++) {
                bool f = false; for (auto v : cardTypes) if (v == i) { f = true; break; }
                float y = (i < 21) ? (i/7) : ((float)((i-21)%2)+0.5f);
                float x = (i < 21) ? (i%7 + 1) : (((i-21)/2) ? 0 : 8);
                glm::vec2 cpos = {(x-4)*0.9f,y*1.4f+1.3f};
                bool hov = mpos.x > cpos.x - .4f && mpos.x < cpos.x + .4f && mpos.y > cpos.y - .6f && mpos.y < cpos.y + .6f;
                if (hov && Mouse::press()) {
                    if (f) {
                        std::vector<int>::iterator position = std::find(cardTypes.begin(), cardTypes.end(), i);
                        cardTypes.erase(position);
                    } else if (cardTypes.size() < 10) {
                        cardTypes.push_back(i);
                    }
                }
            }
            break; }
        case Submenu::SAVESELECT:
            m_app->initGame(2, { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 })->loadGame();
            submenu = Submenu::MAIN;
            break;
    }
}

void Menu::on_render(VertexBatch* batch)
{
    if (submenu == Submenu::CARDSELECT) {
        for (int i = 0; i < 25; i++) {
            Type* t = GameCards::GetGameCardsTypes(i);
            bool f = false; for (auto v : cardTypes) if (v == i) { f = true; break; }
            Card c(t);
            float y = (i < 21) ? (i/7) : ((float)((i-21)%2)+0.5f);
            float x = (i < 21) ? (i%7 + 1) : (((i-21)/2) ? 0 : 8);
            c.set_pos({(x-4)*0.9f,y*1.4f+1.3f,-5});
            c.on_render(batch,false,!f);
        }
    }
}

void Menu::on_renderUI(VertexBatch* batch)
{
    switch (submenu) {
        case Submenu::MAIN:
            btn_LoadGame.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("Load game", btn_LoadGame.getPos(), {0.5f, 0.5f});
            btn_NewGame.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("New game", btn_NewGame.getPos(), {0.5f, 0.5f});
            btn_Quit.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("Quit", btn_Quit.getPos(), {0.5f, 0.5f});
            break;
        case Submenu::PLAYERCOUNT:
            btn_2Pl.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("2 players", btn_2Pl.getPos(), {0.5, 0.5});
            btn_3Pl.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("3 players", btn_3Pl.getPos(), {0.5, 0.5});
            btn_4Pl.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("4 players", btn_4Pl.getPos(), {0.5, 0.5});
            btn_Quit.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("Back", btn_Quit.getPos(), {0.5f, 0.5f});
            SpriteFont::last_created_instance->renderText("Select player count", {0,0.9f}, {1.f,1.f});
            break;
        case Submenu::CARDSELECT:
            btn_Quit.onUpdate(batch);
            SpriteFont::last_created_instance->renderText("Back", btn_Quit.getPos(), {0.5f, 0.5f});
            if (cardTypes.size() == 10) {
                btn_Confirm.onUpdate(batch);
                SpriteFont::last_created_instance->renderText("Start game", btn_Confirm.getPos(), {0.5f, 0.5f});
            }
            SpriteFont::last_created_instance->renderText("Select action cards", {0,0.9f}, {1.f,1.f});
            break;
        case Submenu::SAVESELECT:
            break;
    }
}
