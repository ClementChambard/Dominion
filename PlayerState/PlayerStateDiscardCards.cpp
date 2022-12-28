#include "PlayerStateDiscardCards.hpp"

void PlayerStateDiscardCards::on_tick() {
    // check click on card in hand

    // check press on end discards button
    // then
    // exit_state() -> return is types of card trashed & nb trashed
}

void PlayerStateDiscardCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_played(batch);
    render_piles(batch);
    // Special render hand for hover & discardable
}

void PlayerStateDiscardCards::on_renderUI(VertexBatch* batch) {
    // render end discards button ...
    if (batch) {}
}
