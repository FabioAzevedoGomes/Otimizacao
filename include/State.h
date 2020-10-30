/**
 * This file contains the State class, which models a possible state solution
 * modeled for the problem 
 * 
 * Author: Fábio de Azevedo Gomes
 */

#include <vector>
#include <sstream>
#include <iostream>

#ifndef STATE_H
#define STATE_H

#include "SimulatedAnnealing.h"

// Forward declaration of SimulatedAnnealing
class SimulatedAnnealing;

class State
{
public:
    static int vertex_count; // Number of vertices per state (Same as colors in worst case scenario)
    static State *best;      // The best state found throughout execution

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
     * @param instance Problem instance
     */
    static State *generateStartingState(SimulatedAnnealing *instance);

    /**
     * @brief Generates a neighbor for this state. If neighbor value
     * is better than 'best', update best to generated
     * @param instance Problem instance
     */
    State *generateNeighbor(SimulatedAnnealing *instance);

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

    /**
     * @brief Deletes the best neighbor 
     */
    static void deleteBest();

    /**
     * @brief Sets the state vertex count for the problem
     * @param count Vertex count
     */
    static void setVertexCount(int count);

    /**
     * @brief Checks if this state is OK with the restrictions
     * @returns True if OK, false otherwise 
     */
    bool checkOK(SimulatedAnnealing *instance);
};

#endif