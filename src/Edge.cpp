#include "Edge.h"

Edge::Edge(unsigned int edge_id, unsigned int edge_value, Vertex *v1, Vertex *v2)
{
    this->v1 = v1;
    this->v2 = v2;
    this->id = edge_id;
    this->value = edge_value;
}

Edge::~Edge()
{
    // nil
}

std::pair<Vertex *, Vertex *> Edge::getVertexes()
{
    return std::make_pair(this->v1, this->v2);
}

unsigned int Edge::getValue()
{
    return this->value;
}

unsigned int Edge::getId()
{
    return this->id;
}

void Edge::setId(unsigned int edge_id)
{
    this->id = edge_id;
}

void Edge::setVertexes(std::pair<Vertex *, Vertex *> vertexes)
{
    this->v1 = vertexes.first;
    this->v2 = vertexes.second;
}

void Edge::setValue(double edge_value)
{
    this->value = edge_value;
}
