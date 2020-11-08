#include "Vertex.h"

Vertex::Vertex(unsigned int vertex_id, unsigned int color_id)
{
    this->id = vertex_id;
    this->color = color_id;
}

Vertex::~Vertex()
{
    // nil
}

std::vector<unsigned int> Vertex::getAdjacent()
{
    return this->adjacency_list;
}

void Vertex::setAdjacent(unsigned int vertex_id)
{
    this->adjacency_list.push_back(vertex_id);
}

void Vertex::setId(unsigned int vertex_id)
{
    this->id = vertex_id;
}

void Vertex::setColor(unsigned int color_id)
{
    this->color = color_id;
}

unsigned int Vertex::getColor()
{
    return this->color;
}

unsigned int Vertex::getId()
{
    return this->id;
}

bool Vertex::isAdjacentTo(unsigned int vertex_id)
{
    bool is_adjancent = false;

    for (unsigned int i = 0; !is_adjancent && i < this->adjacency_list.size(); ++i)
        if (this->adjacency_list[i] == vertex_id)
            is_adjancent = true;

    return is_adjancent;
}
