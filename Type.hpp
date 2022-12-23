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
    Type(std::string name, int cost, glm::vec4 uvs);
    ~Type();

    glm::vec4 getUvs() const { return uvs; }

    virtual void onDraw(Player* player) const {} // quand on pioche et on l ajoute a la main
    virtual void onPlay(Player* player)const {}// quand on joue la carte et on l'active
    virtual void onAddToDeck(Player* player)const {} // quand on achete une ou on resoit une malediction et elle part au deck du joueur 
    virtual void onDiscard(Player* player)const {}// quand le joueur defausse une carte depuis sa main 
    virtual void onTrash(Player* player)const {} // quand le joueur jette une carte dans la poubelle permanente


};




#endif // Type_H
