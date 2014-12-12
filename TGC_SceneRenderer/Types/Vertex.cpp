#include "Vertex.h"
using namespace Types;

Vertex::Vertex(void)
{
}

Vertex::Vertex(const glm::vec3 &pos, const glm::vec2 &tex, const const glm::vec3 &normal)
{
    position = pos;
    texCoords = tex;
    normal = normal;
}
