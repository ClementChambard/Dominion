#ifndef PLAYERSTATETRASHCARDS_H_
#define PLAYERSTATETRASHCARDS_H_

#include "PlayerState.hpp"
#include "../CardsType/Type.hpp"

class PlayerStateTrashCards : public PlayerState {
    public:
        PlayerStateTrashCards(Player* p, PlayerState* previousState, int trashsMin, int trashsMax, Type::CardType typeRestriction = Type::CardType::NONE, int costMin = 0, int costMax = 10) :
            PlayerState(p, previousState), m_trashsMin(trashsMin), m_trashsMax(trashsMax), m_typeRestriction(typeRestriction),
            m_costMin(costMin), m_costMax(costMax) {}

        void on_tick() override;
        void on_render(VertexBatch* batch) override;
        void on_renderUI(VertexBatch* batch) override;

        struct Result : PlayerStateResult {
            int nb_card_trashed;
            std::vector<Type*> types_trashed;
        };

    private:
        int m_trashsMin;
        int m_trashsMax;
        Type::CardType m_typeRestriction;
        int m_costMin;
        int m_costMax;
};

#endif // PLAYERSTATETRASHCARDS_H_
