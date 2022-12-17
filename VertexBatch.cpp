#include "VertexBatch.hpp"

VertexBatch::VertexBatch()
{
    glGenBuffers(1, &vbo);
}

VertexBatch::~VertexBatch()
{
    glDeleteBuffers(1, &vbo);
}

void VertexBatch::finish_adding()
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW); //orphan the buffer
    glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());    //upload the data

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
}

void VertexBatch::render(Texture *texture)
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, pos));
    glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

    texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    texture->unbind();
}
