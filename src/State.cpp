#include "State.h"

State *State::best;

State::State(std::vector<int> colors)
{
    // Fill state node list
    this->node_colors = colors;

    // Start value on 0
    this->val = 0;

    // Calculate state value
    for (auto i = this->node_colors.begin(); i != this->node_colors.end(); ++i)
        this->val += *i;
}

State::~State()
{
    // Free vector memory
    this->node_colors.clear();
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
    // Composed string
    std::stringstream output;

    // Compose string by iterating states
    for (auto i = this->node_colors.begin(); i != this->node_colors.end(); ++i)
    {
        output << "State: " << std::distance(this->node_colors.begin(), i) << std::endl;
        output << " Color: " << (*i) << std::endl;
    }

    return output.str();
}

State *State::getBest()
{
    return State::best;
}
