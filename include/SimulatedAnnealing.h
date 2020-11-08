#ifndef SIMULATED_ANNEALING_H
#define SIMULATED_ANNEALING_H

#include <chrono>
#include <cmath>

#include "State.h"
#include "Graph.h"

// ./app <seed> <temperature> <constant> <cooling-factor> <max-neighbors> <max-iterations> <input-file>
int main(int argc, char **argv);

class SimulatedAnnealing
{
private:
    // Input graph
    Graph G;

    // Algorithm values
    double temperature;
    double cooling_factor;
    double constant_k;

    double temperature_min;
    ulong max_neighbors;
    ulong max_iterations;

public:
    /**
     * @brief Algorithm constructor
     * @param t              Temperature
     * @param r              Cooling factor
     * @param k              Constant
     * @param max_neighbors  Number of neighbors generated per iteration
     * @param max_iterations Maximum number of iterations allowed
     * @param filename       File containing graph
     */
    SimulatedAnnealing(double t, double k, double r, unsigned int max_neighbors, unsigned int max_iterations, std::string filename);

    /**
     * @brief Class destructor 
     */
    ~SimulatedAnnealing();

    /**
     * @brief Starts the simulated annealing algorithm 
     */
    void run();
};

#endif // SIMULATED_ANNEALING_H
