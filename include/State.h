#ifndef STATE_H
#define STATE_H

#include <algorithm>
#include <set>

#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "Color.h"

class State
{
private:
    // The graph
    Graph G;

    // State value
    unsigned int value;

    // Best state found
    static State *best;

public:
    /**
     * @brief State constructor 
     * @param graph The state's graph containing vertex, edge and color information
     */
    State(Graph graph);

    /**
     * @brief State destructor 
     */
    ~State();

    /**
     * @brief Computes state value
     * @returns The computed state value 
     */
    unsigned int computeValue();

    /**
     * @brief Returns this state's value
     */
    unsigned int getValue();

    /**
     * @brief Returns best found state 
     */
    static State *getBest();

    /**
     * @brief Copies given state to best found state 
     * @param state the new best sate
     */
    static void setBest(State *state);

    // STARTING STATE AND NEIGHBORHOOD GENERATION

    /**
     * @brief Generates a starting state based on given graph 
     */
    static State *generateStartingState(Graph graph);

    /**
     * @brief Generates a starting state using a greedy
     * color selection strategy 
     */
    static State *greedyStart(Graph graph);

    /**
     * @brief Generates a neighbor for this state
     * @param iteration_number The current iteration
     * @param temperature The current temperature, for dynamic neighbor generation 
     */
    State *generateNeighbor(unsigned int iteration_number, double temperature);

    /**
     * @brief Randomizes the color of n vertexes
     * in this state's graph 
     * @param n Amount of vertices being randomized
     */
    void randomizeVertexColor(unsigned int n);

    /**
     * @brief Performs a local search to attempt
     * to lower the number of colors used by one
     */
    void localSearch();

    // CHECKS AND INFORMATION

    /**
     * @brief Checks if this state is correct, i.e. does not
     * violate the Graph Coloring restrictions
     */
    bool checkCorrectness();

    /**
     * @brief Outputs the state composition to a string format 
     */
    std::string toString();
};

#endif // STATE_H
