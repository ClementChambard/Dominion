#ifndef CARDPILE_H_
#define CARDPILE_H_

#include <vector>
#include "Card.hpp"

class CardPile {
    public:
        CardPile(bool faceUp) : m_faceUp(faceUp) {}
        ~CardPile() = default;

        void AddOnTop(Card* c) { m_data.push_back(c); }
        Card* getOnTop() const { if (m_data.size() == 0) return nullptr; return m_data.back(); }
        void removeOnTop() { if (m_data.size() > 0) m_data.back()->set_hovered(false); m_data.pop_back(); }

        void transmitFrom(CardPile& cp);
        void transmitTo(CardPile& cp) { cp.transmitFrom(*this); }

        void move(glm::vec3 const& pos) { m_targetPos = pos;}
        void setPos(glm::vec3 const& pos) { m_targetPos = m_pos = pos; }
        void setHighlight(bool h) { m_lowlighted = !h; }
        bool isHighlighted() const { return !m_lowlighted; }

        bool isInAnim() const { return m_inAnim; }
        bool isHovered() const;

        void fixPos();
        void shuffle();

        void on_tick();
        void on_render(VertexBatch* batch, bool h = false);

        auto begin() { return m_data.begin(); }
        auto end() { return m_data.end(); }
        auto size() const { return m_data.size(); }

    private:
        bool m_lowlighted = false;
        bool m_inAnim = false;
        bool m_faceUp;
        glm::vec3 m_targetPos {};
        glm::vec3 m_pos {};

        std::vector<Card*> m_data;

};

#endif // CARDPILE_H_
