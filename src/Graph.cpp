#include "Graph.h"

Graph::Graph(std::string filename)
{
    this->used_colors_counter = 0;

    // Try to open file
    std::ifstream in_file(filename, std::ifstream::in);

    if (!in_file.is_open())
        throw std::runtime_error("Input file does not exist!");

    std::string line;  // Line read from file
    std::string token; // Token read from line

    int first, second; // Nodes that are part of an edge

    while (std::getline(in_file, line))
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
            {
                getline(linestream, token, ' '); // 'edge'

                // Get vertex count
                getline(linestream, token, ' ');
                this->vertex_count = atoi(token.c_str());

                // Resize vertex set
                V.resize(this->vertex_count);
                C.resize(this->vertex_count);

                for (uint i = 0; i < this->vertex_count; V[i].setId(i), C[i].setId(i), ++i)
                    ;

                // Get edge count
                getline(linestream, token, ' ');
                this->edge_count = atoi(token.c_str());
            }
            break;
            case 'e': // Edge
            {
                // Get first vertex
                getline(linestream, token, ' ');
                first = atoi(token.c_str());

                // Get second vertex
                getline(linestream, token, ' ');
                second = atoi(token.c_str());

                // Update vertexes
                this->V[first - 1].setAdjacent(second - 1);
                this->V[second - 1].setAdjacent(first - 1);
            }
            break;
            default: // Do nothing
                break;
            }
        }
    }

    // Close file
    in_file.close();
}

Graph::Graph(Graph &graph)
{
    this->V = graph.V;
    this->E = graph.E;
    this->C = graph.C;

    this->edge_count = graph.edge_count;
    this->vertex_count = graph.vertex_count;
    this->used_colors_counter = graph.used_colors_counter;
}

Graph::~Graph()
{
    // nil
}

uint Graph::getVertexCount()
{
    return this->vertex_count;
}

uint Graph::getEdgeCount()
{
    return this->edge_count;
}

uint Graph::getUsedColorCount()
{
    return this->used_colors_counter;
}

std::vector<Vertex> Graph::getVertexes()
{
    return this->V;
}

std::vector<Color> Graph::getColors()
{
    return this->C;
}

std::vector<Color> Graph::getUsedColors()
{
    std::vector<Color> new_vector;

    for (auto i = this->C.begin(); i != this->C.end(); ++i)
    {
        if ((*i).getUsageCounter() > 0)
            new_vector.push_back(*i);
    }

    return new_vector;
}

std::vector<Edge> Graph::getEdges()
{
    return this->E;
}

Vertex *Graph::getVertex(unsigned int vertex_id)
{
    return &this->V[vertex_id];
}

Color *Graph::getColor(unsigned int color_id)
{
    return &this->C[color_id];
}

void Graph::colorVertex(unsigned int vertex_id, unsigned int color_id)
{
    if (this->C[color_id].getUsageCounter() == 0)
        this->used_colors_counter++;

    this->V[vertex_id].setColor(color_id);

    this->C[color_id].addUser(vertex_id);
}

void Graph::cleanVertex(unsigned int vertex_id)
{
    unsigned int color_id = this->V[vertex_id].getColor();

    this->C[color_id].removeUser(vertex_id);

    this->V[vertex_id].setColor(-1);

    if (this->C[color_id].getUsageCounter() == 0)
        this->used_colors_counter--;
}

bool Graph::canUse(unsigned int vertex_id, unsigned int color_id)
{
    bool can_use = true;

    std::vector<unsigned int> adjacent = this->V[vertex_id].getAdjacent();

    for (auto i = adjacent.begin(); can_use && i != adjacent.end(); ++i)
        if (this->V[*i].getColor() == color_id)
            can_use = false;

    return can_use;
}

std::string Graph::outputInfo()
{
    std::stringstream info;

    info << "Vertex count: " << this->vertex_count << std::endl
         << "Edge count: " << this->edge_count << std::endl;

    return info.str();
}
