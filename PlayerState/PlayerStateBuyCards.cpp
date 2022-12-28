#include "PlayerStateBuyCards.hpp"

void PlayerStateBuyCards::on_tick() {
    // check click on pile

    // check buys = 0
    // or
    // check press on end buys button
    // then
    // exit_state()
}

void PlayerStateBuyCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_hand(batch);
    render_played(batch);
    // Special render piles for hover & money
}

void PlayerStateBuyCards::on_renderUI(VertexBatch* batch) {
    // render end buys button
    if (batch) {}
}
