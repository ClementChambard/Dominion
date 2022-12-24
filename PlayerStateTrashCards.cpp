#include "PlayerStateTrashCards.hpp"

void PlayerStateTrashCards::on_tick() {
    // check click on card in hand

    // check press on end trashs button
    // then
    // exit_state()
}

void PlayerStateTrashCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    render_played(batch);
    render_piles(batch);
    // Special render hand for hover & trashable
}

void PlayerStateTrashCards::on_renderUI(VertexBatch* batch) {
    // render end trashs button ...
    if (batch) {}
}
