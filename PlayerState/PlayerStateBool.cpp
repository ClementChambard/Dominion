#include "PlayerStateBool.hpp"

void PlayerStateBool::on_tick() {
    // Check buttons
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
    // TextBox + Text
    // 2 Buttons (Yes/No)
}
