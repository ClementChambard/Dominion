#ifndef SPRITEFONT_H_
#define SPRITEFONT_H_

#include "Texture.hpp"
#include "VertexBatch.hpp"

class SpriteFont {

    public:
        SpriteFont(Texture* t, float h, float v, std::string chars) : font_atlas(t), charNbH(h), charNbV(v), chars(chars) {}
        ~SpriteFont() = default;

        void renderText(std::string text, glm::vec2 pos, glm::vec2 charSize);

        void renderAllText();

    private:
        Texture* font_atlas;
        float charNbH;
        float charNbV;
        std::string chars;
        static VertexBatch* fontBatch;
};

#endif // SPRITEFONT_H_
