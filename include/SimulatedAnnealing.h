/**
 * This file contains the SimulatedAnnealling class, which implements the algorithm
 * of same name using a seed provided during initialization
 * 
 * Author: Fábio de Azevedo Gomes
 */

#include <random>
#include <fstream>
#include <exception>
#include <iostream>

class SimulatedAnnealing
{

private:
    unsigned long seed; // Seed used for randomization
    float k;            // Probability divisor constant
    float r;            // Cooling factor
    float t;            // Current temperature value

public:
    /**
     * @brief Class constructor 
     * @param seed_ Seed for initial value generation
     * @param t_    Initial temperature
     * @param k_    Probability divisor constant
     * @param r_    Cooling factor
     * @param file  File containing the input data
     */
    SimulatedAnnealing(unsigned long seed_, float t_, float k_, float r_, std::string file);

    /**
     * @brief Class destructor 
     */
    ~SimulatedAnnealing();

    /**
     * @brief Starts the algorithm
     * @returns Final value obtained after running the algorithm
     */
    int run();

private:
    /**
     * @brief Prepares the input data into the correct structures for running the algorithm
     * @param file File containing the input data
     * @throw std::exception if input data has the wrong format or file does not exist
     */
    void prepareData(std::ifstream &file);
};