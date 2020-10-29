#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(float t_, float k_, float r_, std::string file)
{
    std::ifstream in_file;

    // Initialize values
    this->k = k_;
    this->temperature = t_;

    // Check cooling factor
    if (r_ <= 0 || r_ >= 1)
        throw new std::runtime_error("Cooling factor must be in the interval (0,1)!");

    this->cooler = r_;

    // Try to open file
    in_file.open(file, std::ifstream::in);

    if (in_file.is_open())
        this->prepareData(in_file);
    else
        throw std::runtime_error("Input file does not exist!");

    // Close file
    in_file.close();

    // Upadte state vertex count
    State::setVertexCount(this->vertex_count);
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    for (auto i = this->adj.begin(); i != this->adj.end(); ++i)
        (*i).clear();

    this->adj.clear();
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

bool SimulatedAnnealing::canUse(int v, int c, std::vector<std::vector<bool>> vertex_colors)
{
    bool can_use = true;

    // Iterate vertex adjacency matrix
    for (int j = 0; can_use && j < this->vertex_count; ++j)
    {
        // If nodes are connected
        if (this->adj[v][j] == 1)
        {
            // If If the same, return false
            if (vertex_colors[j][c])
            {
                can_use = false;
            }
        }
    }

    return can_use;
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

    // Prepate GLPK file
    this->prepareGLPK("../dat/data.dat");

    // Output information about the instance
    this->outputInfo();
}

void SimulatedAnnealing::prepareGLPK(std::string filename)
{
    // File for GLPK-ready output
    std::ofstream data(filename);

    // Write output file opening statement
    data << "data;" << std::endl
         << std::endl;

    // Write vertex set
    data << "# Vertex set (Numbered 0 through N-1)" << std::endl;
    data << "set V :=";
    for (int i = 0; i < this->vertex_count; i++)
    {
        data << " " << i;
    }
    data << ";" << std::endl
         << std::endl;

    // Write color set
    data << "# Color set (Assuming worst case scenario where nColors = nVertexes)" << std::endl;
    data << "set C :=";
    for (int i = 0; i < this->vertex_count; i++)
    {
        data << " " << i;
    }
    data << ";" << std::endl
         << std::endl;

    // Write adjacency matrix
    data << "# Graph adjacency matrix" << std::endl;
    data << "param graph :=" << std::endl;
    for (int i = 0; i < this->vertex_count; i++)
    {
        for (int j = 0; j < this->vertex_count; j++)
        {
            data << " [" << i << ", " << j << "] " << this->adj[i][j];
            if (i < this->vertex_count - 1 || j < this->vertex_count - 1)
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
    int maxNeighbors = 10;     // Number of neighbors generated each iteration
    double lambda = 0.0001;    // Lower limit for temperature before stopping

    // DEBUG
    std::cout << "Generating starting state..." << std::endl;

    // Generate starting state
    State *current_state = State::generateStartingState(this);

    // DEBUG
    std::cout << "Starting state is " << std::endl
              << current_state->getState() << std::endl;
    std::cout << "State correctness is: " << std::endl;
    std::cout << current_state->checkOK(this) << std::endl;

    // While temperature is not 0 (STOP 2)
    while (this->temperature > lambda)
    {
        // Log
        std::cout << "Starting iteration " << iteration_number << std::endl;

        // Calculate new selection probability denominator with new temperature
        prob_kt = this->k * this->temperature;

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
        this->temperature = this->temperature * this->cooler;

        // Increment iteration
        iteration_number++;

        // TODO Save traversed states somewhere so they do not get re-visited?
    }

    // Log
    std::cout << "Finished with " << iteration_number - 1 << " iterations.";

    // Best state
    std::cout << "Best found state uses " << State::getBest()->getValue() << " colors" << std::endl;
    std::cout << State::getBest()->getState() << std::endl;

    // Return best obtained value throughout the algorithm
    return State::getBest()->getValue();
}
