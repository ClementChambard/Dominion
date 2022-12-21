#include <glm/glm.hpp>
#ifndef CARD_H
#define CARD_H

#include "Type.hpp"

class Card
{
private:
    Type type;
    glm::vec3 position;
public:
    Card(Type type);
    ~Card();
};


#endif 



