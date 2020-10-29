#include "State.h"

State *State::best;
int State::vertex_count;

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

State *State::generateStartingState(SimulatedAnnealing *instance)
{
    /**
     * Pseudo-Algorithm for generating starting state:
     * 
     *     // First we take a random starting vertex from all possible ones and color it
     *  1. vertex_list = list (vertex_count) // 0 to N-1
     *  2. color_list = list (vertex_count)  // 0 to N-1
     *  3. Vs = sample (vertex_list);
     *  4. Cs = sample (color_list);
     *  5. vertex_has_color(Vs, Cs) = true
     *  6. vertex_list->remove(Vs)
     * 
     *     // Now that we have a vertex with a color, we can start filling the rest accordingly
     *  7. for (i = 0 i < vertex_count ; i++)
     *  8.   Vi = sample (vertex_list);
     *  9.   vertex_list->remove(Vi)
     * 10.   for (j = 0; j < vertex_count; j++)
     * 11.      if ( Vi->canUse(j) )
     * 12.        vertex_has_color (Vi, j) = true
     * 13.      endif
     * 14.   endfor
     * 15. endfor
     */

    // Vertex coloring matrix and color usage vector
    std::vector<std::vector<bool>> vertex_has_color;
    std::vector<bool> color_is_used(State::vertex_count);

    // Sets with every vertex and color
    std::vector<int> vertexes;
    std::vector<int> colors;

    // Current vertex and color index
    int v_i = -1;
    int c_i = -1;

    // Initialize vertex coloring matrix
    vertex_has_color.resize(State::vertex_count);
    for (int i = 0; i < State::vertex_count; ++i)
        vertex_has_color[i].resize(State::vertex_count);

    // Create a set with every vertex (0 .. N-1)
    for (int i = 0; i < vertex_count; ++i)
        vertexes.insert(vertexes.end(), i);

    // Create a set with every color (0 .. N-1)
    for (int i = 0; i < vertex_count; ++i)
        colors.insert(colors.end(), i);

    // Randomly sample a vertex and color
    v_i = random() % vertexes.size();
    c_i = random() % colors.size();

    // Assign color to vertex
    vertex_has_color[vertexes[v_i]][colors[c_i]] = true;

    // Set color as used
    color_is_used[colors[c_i]] = true;

    // Remove vertex from set
    vertexes.erase(vertexes.begin() + v_i);

    // For every vertex
    for (int i = 0; i < (vertex_count - 1); ++i)
    {
        // Sample random vertex
        v_i = random() % vertexes.size();

        // Find first color
        for (int j = 0; j < vertex_count; ++j)
        {
            if (instance->canUse(vertexes[v_i], j, vertex_has_color))
            {
                // Give color to vertex
                vertex_has_color[vertexes[v_i]][j] = true;

                // Mark color as used
                color_is_used[j] = true;

                // Exit color looping
                j = vertex_count;
            }
        }

        // Remove vertex from list
        vertexes.erase(vertexes.begin() + v_i);
    }

    // Create state with these values
    State *starting_state = new State(vertex_has_color, color_is_used);

    // Return created state
    return starting_state;
}

State *State::generateNeighbor()
{
    // TODO

    // Update best
    State::best = this;

    return this;
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

void State::setVertexCount(int count)
{
    State::vertex_count = count;
}

bool State::checkOK(SimulatedAnnealing *instance)
{
    bool ok = true;

    // Iterate state vertexes
    for (int i = 0; i < State::vertex_count; ++i)
    {
        // Iterate colors
        for (int j = 0; j < State::vertex_count; ++j)
        {
            // If vertex has color
            if (this->vertex_has_color[i][j])
            {
                // Check if can use
                if (!instance->canUse(i, j, this->vertex_has_color))
                {
                    std::cout << "Vertex " << i << " should not be using color " << j << std::endl;
                    ok = false;
                }
            }
        }
    }

    return ok;
}