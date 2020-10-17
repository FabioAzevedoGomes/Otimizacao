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

    int val;                                         // Value of the current state
    std::vector<std::vector<bool>> vertex_has_color; // If vertex v has color c (binary)
    std::vector<bool> color_is_used;                 // If color c is used in the solution

public:
    /**
     * @brief State constructor
     * @param vertex_has_color_ Matrix containing the colors given to each vertex
     * @param color_is_used_    Vector containing information if each color was used
     */
    State(std::vector<std::vector<bool>> vertex_has_color_, std::vector<bool> color_is_used_);

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