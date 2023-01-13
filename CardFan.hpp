#ifndef CARDFAN_H_
#define CARDFAN_H_

#include <vector>
#include "Card.hpp"

class CardFan {
    public:
        CardFan() = default;
        ~CardFan() = default;

        void Add(Card* c) { m_data.push_back(c); }
        Card* get(size_t i) const { if (i >= m_data.size()) return nullptr; return m_data[i]; }
        void remove(size_t i) { if (i >= m_data.size()) return; m_data.erase(std::next(m_data.begin(), i)); }

        int getHoveredId() { return m_hovered; }

        void highlightCard(Type::CardType type) { m_highlighted = type; }

        void move(glm::vec3 const& pos) { m_targetPos = pos;}
        void setPos(glm::vec3 const& pos) { m_targetPos = m_pos = pos; }

        bool isInAnim() const { return m_inAnim; }

        void fixPos();

        void on_tick();
        void on_render(VertexBatch* batch, bool renderHovered = false);

        auto begin() { return m_data.begin(); }
        auto end() { return m_data.end(); }
        auto size() const { return m_data.size(); }
        auto clear() { m_data.clear(); }

    private:
        bool m_inAnim = false;
        int m_hovered = -1;
        glm::vec3 m_targetPos{};
        glm::vec3 m_pos{};

        Type::CardType m_highlighted = Type::CardType::NONE;

        std::vector<Card*> m_data;
};

#endif // CARDFAN_H_
