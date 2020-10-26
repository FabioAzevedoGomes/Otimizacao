#include "State.h"

State *State::best;

State::State(std::vector<std::vector<bool>> vertex_has_color_, std::vector<bool> color_is_used_)
{
    this->vertex_has_color = vertex_has_color_;
    this->color_is_used = color_is_used_;

    for (auto i = this->color_is_used.begin(); i != this->color_is_used.end(); ++i)
    {
        if (*i)
        {
            this->val++;
        }
    }
}

State::~State()
{
    for (auto i = this->vertex_has_color.begin(); i != this->vertex_has_color.end(); ++i)
        (*i).clear();

    this->vertex_has_color.clear();

    this->color_is_used.clear();
}

State *State::generateStartingState()
{
    // TODO

    return NULL;
}

State *State::generateNeighbor()
{
    // TODO

    return NULL;
}

int State::getValue()
{
    return this->val;
}

std::string State::getState()
{
    std::stringstream temp, output;
    int color_count = 0;

    output << " = State description = " << std::endl;

    // Traverse each color
    for (auto i = this->vertex_has_color.begin(); i != this->vertex_has_color.end(); ++i)
        for (auto j = (*i).begin(); j != (*i).end(); ++j)
            if (*j)
                output << " Vertex " << std::distance(this->vertex_has_color.begin(), i) << " has color " << std::distance((*i).begin(), j) << std::endl;

    // Traverse color counter
    for (auto i = this->color_is_used.begin(); i != this->color_is_used.end(); ++i)
        if (*i)
            color_count++;

    // Add information about the color counter
    output << "Total colors used: " << color_count << std::endl;

    // Return
    return output.str();
}

State *State::getBest()
{
    return State::best;
}
