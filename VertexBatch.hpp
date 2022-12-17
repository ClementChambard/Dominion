#ifndef VERTEXBATCH_H_
#define VERTEXBATCH_H_

#include "Shader.hpp"
#include "Texture.hpp"
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 pos = {};
    glm::vec<4, uint8_t> color = {};
    glm::vec2 uv = {};
};

class VertexBatch {
    public:
        VertexBatch();
        ~VertexBatch();

        void clear_vertices() { vertices.clear(); }
        void add_vertex(Vertex const& v) { vertices.push_back(v); }
        void finish_adding();
        void render(Texture* texture);
    private:
        GLuint vbo;
        std::vector<Vertex> vertices;
};

#endif // VERTEXBATCH_H_
