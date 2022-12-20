#include <glm/glm.hpp>

#include <iostream>
#ifndef Type_H
#define Type_H

class Player;

class Type
{
private:
    glm::vec4 uvs;
    int cost;
    std::string name;


public:
    Type();
    ~Type();
    void onDraw(Player* player);
    void onPlay(Player* player);
    void onAddToDeck(Player* player);
    void onDiscard(Player* player);
    void onTrash(Player* player);

};




#endif // Type_H