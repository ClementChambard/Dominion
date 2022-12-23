#ifndef CARDFAN_H_
#define CARDFAN_H_

#include <vector>
#include "Card.hpp"

class CardFan {
    public:
        CardFan() = default;
        ~CardFan() = default;

        void Add(Card* c) { m_data.push_back(c); }
        Card* get(int i) const { if (i < 0 || i >= m_data.size()) return nullptr; return m_data[i]; }
        void remove(int i) { if (i < 0 || i >= m_data.size()) return; m_data.erase(std::next(m_data.begin(), i)); }

        int getHoveredId() { return m_hovered; }

        void move(glm::vec3 const& pos) { m_targetPos = pos;}
        void setPos(glm::vec3 const& pos) { m_targetPos = m_pos = pos; }

        bool isInAnim() const { return m_inAnim; }

        void fixPos();

        void on_tick();
        void on_render(VertexBatch* batch, bool renderHovered = false);

        auto begin() { return m_data.begin(); }
        auto end() { return m_data.end(); }

    private:
        bool m_inAnim = false;
        int m_hovered = -1;
        glm::vec3 m_targetPos{};
        glm::vec3 m_pos{};

        std::vector<Card*> m_data;
};

#endif // CARDFAN_H_
