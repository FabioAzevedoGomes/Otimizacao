#include "Color.h"

Color::Color(unsigned int color_id)
{
    this->id = color_id;
}

Color::~Color()
{
    // nil
}

unsigned int Color::getId()
{
    return this->id;
}

std::vector<unsigned int> Color::getUsers()
{
    return this->used_by;
}

unsigned int Color::getUsageCounter()
{
    return this->used_by.size();
}

void Color::setId(unsigned int color_id)
{
    this->id = color_id;
}

void Color::addUser(unsigned int vertex)
{
    this->used_by.push_back(vertex);
}

void Color::removeUser(unsigned int vertex)
{
    for (auto i = this->used_by.begin(); i != this->used_by.end(); ++i)
    {
        if ((*i) == vertex)
        {
            this->used_by.erase(i);
            return;
        }
    }
}
