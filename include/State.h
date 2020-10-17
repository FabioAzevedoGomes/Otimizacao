/**
 * This file contains the State class, which models a possible state solution
 * modeled for the problem 
 * 
 * Author: Fábio de Azevedo Gomes
 */

#include <list>
#include <vector>
#include <sstream>

#ifndef STATE_H
#define STATE_H

class State
{
private:
    static State *best; // The best state found throughout execution

    int val;                      // Value of the current state
    std::vector<int> node_colors; // Color given to each node

public:
    /**
     * @brief State constructor
     * @param colors List containing colors for each vertex
     */
    State(std::vector<int> colors);

    /**
     * @brief State destructor 
     */
    ~State();

    /**
     * @brief Generates a random starting state based on the given seed 
     */
    static State *generateStartingState();

    /**
     * @brief Generates a neighbor for this state. If neighbor value
     * is better than 'best', update best to generated
     */
    State *generateNeighbor();

    // GETTERS

    /**
     * @brief Returns this state's value 
     */
    int getValue();

    /**
     * @brief Outputs this state composition
     * to a string
     */
    std::string getState();

    /**
     * @brief Returns the best neighbor 
     */
    static State *getBest();
};

#endif