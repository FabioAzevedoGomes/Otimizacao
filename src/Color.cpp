#include "Color.h"

int Color::color_count = 0;

Color::Color()
{
    this->label = Color::color_count;

    Color::color_count++;
}

Color::~Color()
{
    // nil
}

int Color::getLabel()
{
    return this->label;
}

bool Color::isUsed()
{
    return this->vertexes.size() > 0 ? true : false;
}

void Color::setUser(Vertex *vertex)
{
    this->vertexes.push_back(vertex);
}
