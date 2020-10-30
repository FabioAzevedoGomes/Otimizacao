#include "Vertex.h"

int Vertex::vertex_count = 0;

Vertex::Vertex()
{
    this->label = Vertex::vertex_count;

    Vertex::vertex_count++;
}

Vertex::~Vertex()
{
    //nil
}

// Getters

Color *Vertex::getColor()
{
    return this->color;
}

int Vertex::getLabel()
{
    return this->label;
}

std::vector<Vertex *> Vertex::getAdjacency()
{
    return this->adjacent_to;
}

// Setters
void Vertex::setColor(Color *color)
{
    if (this->canUse(color))
        this->color = color;
}

void Vertex::addAdjacent(Vertex *vertex)
{
    this->adjacent_to.push_back(vertex);
}

// Checkers
bool Vertex::canUse(Color *color)
{
    for (auto i = this->adjacent_to.begin(); i != this->adjacent_to.end(); ++i)
        if (color->getLabel() == (*i)->getColor()->getLabel())
            return false;

    return true;
}
