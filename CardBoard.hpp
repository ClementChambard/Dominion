#ifndef CARDBOARD_H_
#define CARDBOARD_H_

#include <vector>
#include "Card.hpp"

class CardBoard {
    public:
        CardBoard() = default;
        ~CardBoard() = default;

        void Add(Card* c) { m_data.push_back(c); }
        Card* get(size_t i) const { if (i >= m_data.size()) return nullptr; return m_data[i]; }
        void remove(size_t i) { if (i >= m_data.size()) return; m_data.erase(std::next(m_data.begin(), i)); }

        void move(glm::vec3 const& pos) { m_targetPos = pos;}
        void setPos(glm::vec3 const& pos) { m_targetPos = m_pos = pos; }

        void fixPos();

        void on_tick();
        void on_render(VertexBatch* batch);

        auto begin() { return m_data.begin(); }
        auto end() { return m_data.end(); }
        auto size() { return m_data.size(); }

    private:
        glm::vec3 m_targetPos{};
        glm::vec3 m_pos{};

        std::vector<Card*> m_data;
};

#endif // CARDBOARD_H_
