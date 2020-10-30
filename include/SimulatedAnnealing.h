/**
 * This file contains the SimulatedAnnealing class, which implements the algorithm
 * of same name using a seed provided during initialization
 * 
 * Author: Fábio de Azevedo Gomes
 */

#ifndef SIMMULATED_ANNEALING_H
#define SIMMULATED_ANNEALING_H

#include <random>
#include <fstream>
#include <exception>
#include <iostream>
#include <limits>
#include <cmath>

#include "State.h"

// Forward declaration of State
class State;

class SimulatedAnnealing
{

private:
    float k;           // Probability divisor constant
    float cooler;      // Cooling factor
    float temperature; // Current temperature value

    int vertex_count;                  // Number of vertexes in the input graph
    int edge_count;                    // Number of edges in the input graph
    std::vector<std::vector<int>> adj; // Adjacency matrix for the input graph

public:
    /**
     * @brief Class constructor 
     * @param t_    Initial temperature
     * @param k_    Probability divisor constant
     * @param r_    Cooling factor
     * @param file  File containing the input data
     */
    SimulatedAnnealing(float t_, float k_, float r_, std::string file);

    /**
     * @brief Class destructor 
     */
    ~SimulatedAnnealing();

    /**
     * @brief Starts the algorithm
     * @returns Final value obtained after running the algorithm
     */
    int run();

    /**
     * @brief Outputs the problem instance information, such as the
     * total number of vertices, edges and the adjacency matrix
     */
    void outputInfo();

    /**
     * @brief Returns true if vertex v can receive color c, false otherwise
     * @param v Vertex number
     * @param c Color number
     * @param vertex_colors Matrix containing the color given to each vertex so far
     */
    bool canUse(int v, int c, std::vector<std::vector<bool>> vertex_colors);

    /**
     * @brief Returns adjacency matrix size (square matrix) 
     */
    int getSize();

    /**
     * @brief Returns the graph adjacency matrix 
     */
    std::vector<std::vector<int>> getAdjacencyMatrix();

private:
    /**
     * @brief Prepares the input data into the correct structures for running the algorithm
     * @param file File containing the input data
     * @throw std::runtime_error if input data has the wrong format or file does not exist
     */
    void prepareData(std::ifstream &file);

    /**
     * @brief Prepares a GLPK formatted param file for use with the
     * solver, based on the input data 
     * @param filename Output file name
     */
    void prepareGLPK(std::string filename);
};

#endif