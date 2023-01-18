#include "PlayerStateBool.hpp"
#include "../SpriteFont.hpp"
#include "../Mouse.hpp"

Button PlayerStateBool::no{{247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{0.3f,-0.2f},{0.3f,0.2f}};
Button PlayerStateBool::yes{{247/600.f,365/500.f,424/600.0f,445/500.f},{247/600.f,271/500.f,424/600.0f,350/500.f},{-0.3f,-0.2f},{0.3f,0.2f}};

void PlayerStateBool::on_tick() {
    if (yes.isHovered() && Mouse::press()) exit_state(new Result{true});
    if (no.isHovered() && Mouse::press()) exit_state(new Result{false});
}

void PlayerStateBool::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_piles(batch);
    render_played(batch);
    render_hand(batch);
}

void PlayerStateBool::on_renderUI(VertexBatch* batch) {
    batch->draw_rectangle(0, 0, 0, 2, 2, glm::mat4(1.f), {0,0,0,0}, {0,0,0,120});
    no.onUpdate(batch);
    yes.onUpdate(batch);
    SpriteFont::last_created_instance->renderText("Yes", yes.getPos(), {0.5, 0.5});
    SpriteFont::last_created_instance->renderText("No", no.getPos(), {0.5, 0.5});
    SpriteFont::last_created_instance->renderText(m_question, {0, 0.2}, {1, 1});
}
