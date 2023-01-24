#include "PlayerStateBuyCards.hpp"
#include "../Player.hpp"
#include "../Game.hpp"
#include "../Mouse.hpp"
#include "../SpriteFont.hpp"

void PlayerStateBuyCards::on_entry() {
    // highlight can buy piles
    player()->getGame()->highlightPiles(m_typeRestriction, m_money);
}

void PlayerStateBuyCards::on_exit() const {
    // un-highlight piles
    player()->getGame()->highlightPiles(Type::CardType::NONE, 100);
}

void PlayerStateBuyCards::on_tick() {
    // check buys = 0
    if (m_buys <= 0) { exit_state(nullptr); return; }
    // check click on pile
    int hoveredPile = player()->getGame()->getHoveredPileId();
    if (hoveredPile >= 0) {
        auto p = player()->getGame()->getPile(hoveredPile);
        auto type = p.getOnTop()->getType();
        // check has enough money and click
        if (type->isType(m_typeRestriction) && type->getCost() <= m_money && Mouse::press())
        {
            m_buys--;
            m_money -= type->getCost();
            if (m_updatePlayerMoney) { player()->addBuys(-1); player()->addCoins(-type->getCost()); }
            player()->getGame()->DistributeCard(player(), hoveredPile, directhand ? PlayerCards::HAND : PlayerCards::BOARD);
            player()->getGame()->highlightPiles(m_typeRestriction, m_money);
        }
    }
    // check press on end buys button
    if (m_button.isHovered() && Mouse::press()) { exit_state(nullptr); return; }
}

void PlayerStateBuyCards::on_render(VertexBatch* batch) {
    render_deck(batch);
    render_discard(batch);
    player()->getGame()->render_piles(batch, true);
    render_played(batch);
    render_hand(batch);
}

void PlayerStateBuyCards::on_renderUI(VertexBatch* batch) {
   PlayerState::m_button.onUpdate(batch);
   SpriteFont::last_created_instance->renderText("End buys", m_button.getPos(), {0.6f, 0.6f});
}
