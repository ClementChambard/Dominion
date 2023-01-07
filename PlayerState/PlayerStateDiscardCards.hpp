#ifndef PLAYERSTATEDISCARDCARDS_H_
#define PLAYERSTATEDISCARDCARDS_H_

#include "PlayerState.hpp"
#include "../CardsType/Type.hpp"

class PlayerStateDiscardCards : public PlayerState {
    public:
        PlayerStateDiscardCards(Player* p, PlayerState* previousState, 
        int discardsMin, int discardsMax, Type::CardType typeRestriction = Type::CardType::NONE) :
            PlayerState(p, previousState), m_discardsMin(discardsMin), m_discardsMax(discardsMax), m_typeRestriction(typeRestriction) { on_entry(); }

        void on_entry() override {}
        void on_exit() const override {}
        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;

        struct Result : PlayerStateResult {
            int nb_card_discarded;
            std::vector<Type*> types_discarded;
        };

    private:
        int m_discardsMin;
        int m_discardsMax;
        Type::CardType m_typeRestriction;
};

#endif // PLAYERSTATEDISCARDCARDS_H_
