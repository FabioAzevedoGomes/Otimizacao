#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(float t_, float k_, float r_, std::string file)
{
    std::ifstream in_file;

    // Initialize values
    this->k = k_;
    this->r = r_;
    this->t = t_;

    // Try to open file
    in_file.open(file, std::ifstream::in);

    if (in_file.is_open())
        this->prepareData(in_file);
    else
        throw std::runtime_error("Input file does not exist!");

    // Close file
    in_file.close();
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    // TODO Free data structures used
}

void SimulatedAnnealing::outputInfo()
{
    // Output information about problem dimensions
    std::cout << "Problem dimensions are: " << std::endl;
    std::cout << "* " << this->vertex_count << " vertices" << std::endl;
    std::cout << "* " << this->edge_count << " edges" << std::endl;

    // Output adjacency matrix
    std::cout << "Adjacency matrix is: " << std::endl;
    for (int i = 0; i < this->vertex_count; ++i)
    {
        for (int j = 0; j < this->vertex_count; ++j)
            std::cout << this->adj[i][j] << " ";
        std::cout << std::endl;
    }
}

void SimulatedAnnealing::prepareData(std::ifstream &file)
{
    std::string line;  // Line read from file
    std::string token; // Token read from line

    int first, second; // Nodes that are part of an edge

    while (std::getline(file, line))
    {
        // Ignore blank lines
        if (line.size() > 0)
        {
            // Stream input line
            std::stringstream linestream(line);

            // Get line descriptor token
            getline(linestream, token, ' ');

            // Check information type
            switch (token.at(0))
            {
            case 'p': // Definition of graph

                getline(linestream, token, ' '); // 'edge'

                // Get vertex count
                getline(linestream, token, ' ');
                this->vertex_count = atoi(token.c_str());

                // Set adjacency matrix size
                this->adj.resize(this->vertex_count);
                for (int i = 0; i < this->vertex_count; ++i)
                    this->adj[i].resize(this->vertex_count);

                // Get edge count
                getline(linestream, token, ' ');
                this->edge_count = atoi(token.c_str());

                break;
            case 'e': // Edge

                // Get first vertex
                getline(linestream, token, ' ');
                first = atoi(token.c_str());

                // Get second vertex
                getline(linestream, token, ' ');
                second = atoi(token.c_str());

                // Update adjacency matrix
                adj[first - 1][second - 1] = 1;
                adj[second - 1][first - 1] = 1;

                break;
            default: // Do nothing
                break;
            }
        }
    }
    // Output information about the instance
    this->outputInfo();

    std::exit(0);
}

// ALGORITHM LOGIC

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
int SimulatedAnnealing::run()
{
    double prob_kt = 0;        // Probability that a worse state will be chosen
    uint iteration_number = 1; // Current iteration number
    State *neighbor;           // Generated neighbor for a state
    int maxNeighbors = 0;      // Number of neighbors generated each iteration

    // Generate starting state
    State *current_state = State::generateStartingState();

    // While temperature is not 0 (STOP 2)
    while (this->t > 0)
    {
        // Log
        std::cout << "Starting iteration " << iteration_number << std::endl;

        // Calculate new selection probability denominator with new temperature
        prob_kt = this->k * this->t;

        // Iterate neighbors (STOP 1)
        for (int i = 0; i < maxNeighbors; ++i)
        {
            // Generate neighbor
            neighbor = current_state->generateNeighbor();

            // If neighbor value is better than current value
            if (neighbor->getValue() <= current_state->getValue())
            {
                current_state = neighbor; // Update current state
            }
            else
            {
                // With 1.0e-((f(s') - f(s))/k*t) probability
                if (random() / RAND_MAX < std::exp(-(neighbor->getValue() - current_state->getValue()) / prob_kt))
                {
                    // Assign worse state anyways
                    current_state = neighbor;
                }
            }
        }

        // Decrease temperature
        this->t = this->t * this->r;

        // Increment iteration
        iteration_number++;

        // TODO Save traversed states somewhere so they do not get re-visited?
    }

    // Return best obtained value throughout the algorithm
    return State::getBest()->getValue();
}
