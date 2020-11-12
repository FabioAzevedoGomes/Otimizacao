#include "State.h"

State *State::best = NULL;

State::State(Graph graph) : G(graph)
{
    this->value = 0;

    // Compute state value
    this->computeValue();
}

State::~State()
{
    // nil
}

unsigned int State::computeValue()
{
    this->value = G.getUsedColorCount();

    return this->value;
}

unsigned int State::getValue()
{
    return this->value;
}

State *State::getBest()
{
    return State::best;
}

void State::setBest(State *state)
{
    if (State::best != NULL)
        delete State::best;

    State::best = new State(state->G);
}

State *State::generateStartingState(Graph graph)
{
    State *starting_state = NULL;

    // Generate starting state
    starting_state = State::greedyStart(graph);

    // Update best state
    State::setBest(starting_state);

    // Return generated state
    return starting_state;
}

State *State::greedyStart(Graph graph)
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

    State *new_state = NULL;

    // Copy graph
    Graph G(graph);

    // Sets with every vertex id
    std::vector<unsigned int> vertex_ids;
    for (unsigned int i = 0; i < G.getVertexCount(); ++i)
        vertex_ids.push_back(i);

    // Randomize a vertex
    unsigned int v_i = random() % vertex_ids.size();

    // Give color 0 to vertex
    G.colorVertex(v_i, 0);

    // Remove vertex from list
    vertex_ids.erase(vertex_ids.begin() + v_i);

    // Iterate remaining vertexes
    for (unsigned int i = 0; i < G.getVertexCount() - 1; ++i)
    {
        // Sample random vertex
        v_i = random() % vertex_ids.size();

        // Iterate colors
        for (unsigned int j = 0; j < G.getVertexCount(); ++j)
        {
            // If vertex can use color
            if (G.canUse(vertex_ids[v_i], j))
            {
                // Give color to vertex
                G.colorVertex(vertex_ids[v_i], j);

                // Exit color looping
                j = G.getVertexCount();
            }
        }

        // Remove vertex from list
        vertex_ids.erase(vertex_ids.begin() + v_i);
    }

    // Create state with these values
    new_state = new State(G);

    // Return created state
    return new_state;
}

State *State::generateNeighbor(unsigned int iteration_number, double temperature)
{
    // Generate new neighbor with the same graph as this one
    State *neighbor = new State(this->G);

    // Randomize color given to vertex
    neighbor->randomizeVertexColor(1);

    if (((double)random() / RAND_MAX) >= 0.8)
        neighbor->localSearch();

    // If better than best, update best
    if (neighbor->getValue() < State::best->getValue())
        State::setBest(neighbor);

    neighbor->checkCorrectness();

    // Return neighbor
    return neighbor;
}

void State::randomizeVertexColor(unsigned int n)
{
    unsigned int v_i = (unsigned int)-1;
    unsigned int c_i = (unsigned int)-1;
    std::vector<unsigned int> unavailable_colors;
    std::vector<unsigned int> available_colors;
    std::vector<unsigned int> adjacency;
    std::vector<unsigned int> all_colors;

    // Create set with all colors
    for (unsigned int i = 0; i < this->G.getVertexCount(); ++i)
        all_colors.push_back(i);

    // Repeat n times
    for (unsigned int i = 0; i < n; ++i)
    {
        // Reset variables
        unavailable_colors.clear();
        available_colors.clear();
        adjacency.clear();

        // Take a random vertex and get it's adjacency list
        v_i = random() % this->G.getVertexCount();
        adjacency = this->G.getVertex(v_i)->getAdjacent();

        // Create set of unavailable colors for that vertex
        for (unsigned int i = 0; i < adjacency.size(); ++i)
            unavailable_colors.push_back(this->G.getVertex(adjacency[i])->getColor());

        // Remove duplicates
        std::set<unsigned int> s(unavailable_colors.begin(), unavailable_colors.end());
        unavailable_colors.assign(s.begin(), s.end());

        // Sort
        std::sort(unavailable_colors.begin(), unavailable_colors.end());

        // Set diff = available colors
        std::set_difference(all_colors.begin(), all_colors.end(),
                            unavailable_colors.begin(), unavailable_colors.end(),
                            std::inserter(available_colors, available_colors.begin()));

        // Remove old vertex color
        this->G.cleanVertex(v_i);

        // Get random color
        c_i = random() % available_colors.size();
        c_i = available_colors[c_i];

        // If this is higher than current state value
        if (c_i > this->value)
        {
            for (int i = available_colors.size() - 1; i >= 0; --i)
            {
                if (available_colors[i] < this->value)
                {
                    c_i = available_colors[(unsigned int)i == available_colors.size() - 1 ? i : i + 1];
                    i = -1;
                }
            }
        }

        // Give new color to vertex
        this->G.colorVertex(v_i, c_i);

        // Recompute value
        this->computeValue();
    }

    // Return
    return;
}

void State::localSearch()
{
    // Select random, used color
    std::vector<Color> used_colors = this->G.getUsedColors();
    unsigned int c_i = random() % used_colors.size();
    c_i = used_colors[c_i].getId();

    // Remove that color from every vertex that uses it
    std::vector<unsigned int> users = this->G.getColor(c_i)->getUsers();
    for (auto i = users.begin(); i < users.end(); ++i)
    {
        // Remove color
        this->G.cleanVertex((*i));

        // Find new color
        for (unsigned int j = 0; j < this->G.getVertexCount(); ++j)
        {
            if (this->G.canUse((*i), j))
            {
                // Assign color
                this->G.colorVertex((*i), j);

                // Exit color looping
                j = this->G.getVertexCount() + 1;
            }
        }
    }

    // Recompute value
    this->computeValue();
}

bool State::checkCorrectness()
{
    bool ok = true;

    std::vector<Vertex> vertexes = this->G.getVertexes();

    // Iterate state vertexes
    for (auto i = vertexes.begin(); i != vertexes.end(); ++i)
    {
        // Check if vertex has a color
        if ((*i).getColor() == (uint)-1)
        {
            std::cerr << "[ERROR]: Vertex " << (*i).getId() << " has no color" << std::endl;
            ok = false;
        }
        // Check if it can use it's color
        if (!this->G.canUse((*i).getId(), (*i).getColor()))
        {
            std::cerr << "[ERROR]: Vertex " << (*i).getId() << " should not have color " << (*i).getColor() << std::endl;
            ok = false;
        }
    }

    return ok;
}

std::string State::toString()
{
    std::stringstream info;

    // Iterate vertex list
    std::vector<Vertex> vertexes = this->G.getVertexes();
    for (auto i = vertexes.begin(); i != vertexes.end(); ++i)
        // Output color
        std::cout << "[INFO]: Vertex " << (*i).getId() << " has color " << (*i).getColor() << std::endl;

    // Outpupt value
    std::cout << "[INFO]: Total colors used: " << this->value << std::endl;

    // Return
    return info.str();
}
