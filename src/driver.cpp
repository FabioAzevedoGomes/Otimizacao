/**
 * Driver code for running the simmulated annealing arlgorithm
 * 
 * Author: Fábio de Azevedo Gomes 
 */

#include <iostream>

#include "SimulatedAnnealing.h"

// ./app <seed> <temperature> <constant> <cooling-factor> <input-file>
int main(int argc, char **argv)
{
    // Operation result returned by the simulated annealing arlgorithm
    int result;
    SimulatedAnnealing *sa = NULL;

    // Parse command line input
    if (argc < 6)
    {
        std::cerr << "Usage: " << argv[0] << " <seed> <temperature> <constant> <cooling-factor> <input-file>" << std::endl;
        return -1;
    }

    // Set psudo-random seed
    srand(atol(argv[1]));

    try
    {
        // Create instance of simulated annealing
        sa = new SimulatedAnnealing(atof(argv[2]), atof(argv[3]), atof(argv[4]), argv[5]);

        // Run
        result = sa->run();
    }
    catch (std::runtime_error &e)
    {
        // Error
        std::cerr << e.what() << std::endl;

        return -1;
    }

    // Finish returning result value
    return result;
}