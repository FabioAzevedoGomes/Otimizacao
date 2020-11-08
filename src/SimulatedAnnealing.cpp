#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(double t, double k, double r, unsigned int max_neighbors, unsigned int max_iterations, std::string filename) : G(filename)
{
    this->temperature = t;
    this->cooling_factor = r;
    this->constant_k = k;
    this->max_iterations = max_iterations;
    this->max_neighbors = max_neighbors;

    // File for GLPK-ready output
    std::ofstream data("data.dat");

    // Write output file opening statement
    data << "data;" << std::endl
         << std::endl;

    // Write big M
    data << "# Big M parameter" << std::endl;
    data << "param M := " << this->G.getVertexCount() << std::endl;

    // Write vertex set
    data << "# Vertex set (Numbered 0 through N-1)" << std::endl;
    data << "set V :=";
    for (unsigned int i = 0; i < this->G.getVertexCount(); i++)
    {
        data << " " << i;
    }
    data << ";" << std::endl
         << std::endl;

    // Write color set
    data << "# Color set (Assuming worst case scenario where nColors = nVertexes)" << std::endl;
    data << "set C :=";
    for (unsigned int i = 0; i < this->G.getVertexCount(); i++)
    {
        data << " " << i;
    }
    data << ";" << std::endl
         << std::endl;

    // Write adjacency matrix
    data << "# Graph adjacency matrix" << std::endl;
    data << "param graph :=" << std::endl;
    for (unsigned int i = 0; i < this->G.getVertexCount(); i++)
    {
        for (unsigned int j = 0; j < this->G.getVertexCount(); j++)
        {
            data << " [" << i << ", " << j << "] " << this->G.getVertex(i)->isAdjacentTo(j);
            if (i < this->G.getVertexCount() - 1 || j < this->G.getVertexCount() - 1)
            {
                data << ",";
            }
        }
        data << std::endl;
    }
    data << ";" << std::endl
         << std::endl;

    // Write output file closing statement
    data << "end;" << std::endl;

    // Close file
    data.close();
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    // nil
}

void SimulatedAnnealing::run()
{
    /**
     * Pseudo-Algorithm:
     *
     * 1. while STOP 2
     * 2.   while STOP 1
     * 3.    Choose s' not visited from N(s)
     * 4.     if f(s') < f(s)
     * 5.       s = s'
     * 6.     else 
     * 7.       s = s' with probability e ^ - (f(s') - f(s)) / k * t
     * 8.    t = t * r
     * 9. return s
     */

    double prob_kt = 0;        // Probability that a worse state will be chosen
    uint iteration_number = 1; // Current iteration number

    std::vector<State *> neighbors;
    State *neighbor = NULL; // Generated neighbor for a state

    double lambda = 0.00000001; // Lower limit for temperature before stopping

    // Log files
    std::ofstream log_file("log.dat");
    std::ofstream neigh_file("neighbors.dat");

    // Output information
    std::cout << "[INFO]: Generating starting state..." << std::endl;

    // Start measuring time
    auto start = std::chrono::system_clock::now();

    // Generate starting state
    State *current_state = State::generateStartingState(this->G);

    std::cout << "[INFO]: Done." << std::endl;

    // While temperature is not 0 (STOP 2)
    while (this->temperature > lambda)
    {
        // Log
        std::cout << "========================================================" << std::endl;
        std::cout << "[INFO]: Iteration: " << iteration_number << std::endl;
        std::cout << "[INFO]: Temperature: " << this->temperature << std::endl;
        std::cout << "[INFO]: Selection probability denominator (k*t): " << prob_kt << std::endl;
        std::cout << "[INFO]: Current state value: " << current_state->getValue() << std::endl;
        log_file << iteration_number << "  " << current_state->getValue() << std::endl;

        // Calculate new selection probability denominator with new temperature
        prob_kt = this->constant_k * this->temperature;

        neighbors.clear();
        for (unsigned int i = 0; i < this->max_neighbors; ++i)
        {
            neighbor = current_state->generateNeighbor(iteration_number, this->temperature);
            neighbors.push_back(neighbor);
        }

        // Iterate neighbors (STOP 1)
        for (unsigned int i = 0; i < this->max_neighbors; ++i)
        {
            // Get neighbor
            neighbor = neighbors[i];

            // Log
            neigh_file << iteration_number << "  " << neighbor->getValue() << std::endl;

            // If neighbor value is better than current value
            if (neighbor->getValue() <= current_state->getValue())
            {
                // Update current state
                delete current_state;
                current_state = neighbor;
            }
            else
            {
                // With 1.0e-((f(s') - f(s))/k*t) probability
                if (random() / RAND_MAX < std::exp(-(double)(neighbor->getValue() - current_state->getValue()) / prob_kt))
                {
                    // Assign worse state anyways
                    delete current_state;
                    current_state = neighbor;
                }
                else
                {
                    // If neighbor was ignored, delete it
                    delete neighbor;
                }
            }
        }
        neigh_file << std::endl;

        // Decrease temperature
        this->temperature = this->temperature * this->cooling_factor;

        // Increment iteration
        iteration_number++;
    }

    // Stop timer
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    // Free memory
    delete current_state;

    // Get best state
    current_state = State::getBest();

    // Check if final state is correct
    current_state->checkCorrectness();

    // Best state
    std::cout << "[INFO]: Best found state uses " << current_state->getValue() << " colors" << std::endl;
    std::cout << current_state->toString() << std::endl;

    // Log
    std::cout << "[INFO]: Finished in " << elapsed_seconds.count() << " seconds" << std::endl
              << "[INFO]: Total iterations: " << iteration_number - 1 << std::endl;

    // Close log files
    log_file.close();
    neigh_file.close();

    // Free memory
    delete current_state;

    // Return
    return;
}

int main(int argc, char **argv)
{
    // Parse command line input
    if (argc < 8)
    {
        std::cerr << "Usage: " << argv[0] << " <seed> <temperature> <constant> <cooling-factor> <max-neighbors> <max-iterations> <input-file>" << std::endl;
        return -1;
    }

    // Set psudo-random seed
    srandom(atol(argv[1]));

    // Create instance of simulated annealing with given parameters
    SimulatedAnnealing algorithm(atof(argv[2]), atof(argv[3]), atof(argv[4]), atoi(argv[5]), atoi(argv[6]), argv[7]);

    // Run algorithm
    algorithm.run();

    // Exit
    return 0;
}
