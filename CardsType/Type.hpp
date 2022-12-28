#ifndef Type_H
#define Type_H

#include <glm/glm.hpp>
#include <iostream>
#include <vector>

class Player;


class Type
{
public:
    enum class CardType {
        NONE = -1,
        ACTION,
        VICTORY,
        TREASURE,
        REACTION,
        ATTACK,
    };

private:
    std::vector<CardType> types;
    std::string name;
    glm::vec4 uvs;
    int cost;

public:

    Type(std::string name, int cost, glm::vec4 uvs, std::vector<CardType> const& types) : types(types), name(name), uvs(uvs), cost(cost) {}
    virtual ~Type() = default;

    bool isType(CardType t) const;

    std::string getName() const { return name; }
    int getCost() const { return cost; }
    glm::vec4 getUvs() const { return uvs; }

    virtual void onDraw(Player* player) const;
    virtual void onPlay(Player* player) const;
    virtual void onAddToDeck(Player* player) const;
    virtual void onDiscard(Player* player) const;
    virtual void onTrash(Player* player) const;
    virtual void onDeckChange(Player* player, int oldCardNumber, int newCardNumber) const;
    virtual bool onReact(Player* player) const;
};




#endif // Type_H
