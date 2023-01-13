#include "PlayerStateActions.hpp"
#include "../Player.hpp"
#include "../Mouse.hpp"

void PlayerStateActions::on_entry() {
    player()->getHand().highlightCard(Type::CardType::ACTION);
}

void PlayerStateActions::on_exit() const {
    player()->getHand().highlightCard(Type::CardType::NONE);
}

void PlayerStateActions::on_tick() {
    std::cout << "tick " << player()->getActions() << "\n";
    // check nb of actions left
    if (player()->getActions() <= 0) { exit_state(nullptr); return; }
    // check if player has action cards in hand
    bool hasAction = false;
    for (auto c : player()->getHand()) if (c->getType()->isType(Type::CardType::ACTION)) hasAction = true;
    if (!hasAction) { exit_state(nullptr); return; }
    // check if player is clicking on action card in hand
    int hoveredCard = player()->getHand().getHoveredId();
    if (hoveredCard >= 0) {
        Card* c = player()->getHand().get(hoveredCard);
        // If card is action card and mouse click : play it
        if (Mouse::press() && c->getType()->isType(Type::CardType::ACTION))
        {
            player()->getHand().remove(hoveredCard);
            player()->getBoard().Add(c);
            player()->playCard(c);
        }
    }
    // check if player clicks the buy button
    if (m_button.isHovered() && Mouse::press()) { exit_state(nullptr); return; }
}

void PlayerStateActions::on_render(VertexBatch* batch) {

    render_deck(batch);
    render_discard(batch);
    render_piles(batch);
    render_played(batch);
    player()->getHand().on_render(batch, true);
}

void PlayerStateActions::on_renderUI(VertexBatch* batch) {
    m_button.onUpdate(batch);
}
