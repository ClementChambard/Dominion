#include "PlayerStateActions.hpp"

void PlayerStateActions::on_tick() {
    // check if player is clicking on action card in hand
    // check if player clicks the buy button
}

void PlayerStateActions::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_piles(batch);
    render_played(batch);
    // special render hand
}

void PlayerStateActions::on_renderUI(VertexBatch* batch) {
    // render buy button
    if (batch) {}
}
