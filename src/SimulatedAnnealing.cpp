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
    // Delete adjacency matrix
    for (auto i = this->adj.begin(); i != this->adj.end(); ++i)
        (*i).clear();

    this->adj.clear();

    // delete vertexes
    for (int i = 0; i < this->vertex_count; ++i)
        delete this->vertexes[i];
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

    Vertex *vertex = this->vertexes[v];
    std::vector<Vertex *> adjacent_to = vertex->getAdjacency();

    for (auto i = adjacent_to.begin(); can_use && i != adjacent_to.end(); ++i)
    {
        if (vertex_colors[(*i)->getLabel()][c])
        {
            can_use = false;
        }
    }

    return can_use;
}

void SimulatedAnnealing::prepareData(std::ifstream &file)
{
    std::string line;  // Line read from file
    std::string token; // Token read from line

    int first, second; // Nodes that are part of an edge

    Vertex *vertex = NULL;

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

                // Set adjacency matrix size and create vertexes
                this->adj.resize(this->vertex_count);
                for (int i = 0; i < this->vertex_count; ++i)
                {
                    // Resize adjacency matrix
                    this->adj[i].resize(this->vertex_count);

                    // Create vertex and add to list
                    vertex = new Vertex();
                    vertexes.push_back(vertex);
                }

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

                // Update vertexes
                this->vertexes[first - 1]->addAdjacent(this->vertexes[second - 1]);
                this->vertexes[second - 1]->addAdjacent(this->vertexes[first - 1]);

                break;
            default: // Do nothing
                break;
            }
        }
    }

    // Prepate GLPK file
    this->prepareGLPK("../dat/data.dat");
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

int SimulatedAnnealing::getSize()
{
    return this->vertex_count;
}

std::vector<std::vector<int>> SimulatedAnnealing::getAdjacencyMatrix()
{
    return this->adj;
}

// ALGORITHM LOGIC

int SimulatedAnnealing::run()
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
    State *neighbor = NULL;    // Generated neighbor for a state
    int maxNeighbors = 10;     // Number of neighbors generated each iteration
    double lambda = 0.0001;    // Lower limit for temperature before stopping

    std::ofstream log_file("log.txt"); // For logging state progression

    DEBUG_LOG(outputInfo());

    std::cout << "Generating starting state..." << std::endl;

    // Start measuring time
    auto start = std::chrono::system_clock::now();

    // Generate starting state
    State *current_state = State::generateStartingState(this);

    std::cout << "Done." << std::endl;

    // While temperature is not 0 (STOP 2)
    while (this->temperature > lambda)
    {
        // Log
        std::cout << "Starting iteration " << iteration_number << std::endl;
        log_file << "Iteration: " << iteration_number << std::endl
                 << "Current state value: " << current_state->getValue() << std::endl;

        // Calculate new selection probability denominator with new temperature
        prob_kt = this->k * this->temperature;

        // Iterate neighbors (STOP 1)
        for (int i = 0; i < maxNeighbors; ++i)
        {
            // Generate neighbor
            neighbor = current_state->generateNeighbor(this);

            // If neighbor value is better than current value
            if (neighbor->getValue() <= current_state->getValue())
            {
                DEBUG_LOG(std::cout << "Updated current state to neighbor" << std::endl);

                // Update current state
                delete current_state;
                current_state = neighbor;
            }
            else
            {
                // With 1.0e-((f(s') - f(s))/k*t) probability
                if (random() / RAND_MAX < std::exp(-(abs(neighbor->getValue() - current_state->getValue())) / prob_kt))
                {
                    DEBUG_LOG(std::cout << "Updated current state to neighbor even though it had worse value" << std::endl);

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

        // Decrease temperature
        this->temperature = this->temperature * this->cooler;

        // Increment iteration
        iteration_number++;
    }

    // Stop timer
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    // Log
    std::cout << "Finished in " << elapsed_seconds.count() << " seconds" << std::endl
              << "Total iterations: " << iteration_number - 1 << std::endl;

    // Check if final state is OK
    State::getBest()->checkOK(this);

    // Best state
    int best_state_value = State::getBest()->getValue();
    std::cout << "Best found state uses " << best_state_value << " colors" << std::endl;
    std::cout << State::getBest()->getState() << std::endl;

    // Free memory
    delete current_state;
    State::deleteBest();

    // Close log file
    log_file.close();

    // Return best state's value
    return best_state_value;
}
