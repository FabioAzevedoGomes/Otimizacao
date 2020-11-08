#ifndef EDGE_H
#define EDGE_H

#include "Vertex.h"

class Edge
{
private:
    // The two vertices that this edge connects
    Vertex *v1;
    Vertex *v2;

    // Edge unique identifier
    unsigned int id;

    // Edge value / cost
    double value;

public:
    /**
     * @brief Edge constructor 
     */
    Edge(unsigned int edge_id = 0, unsigned int edge_value = 0, Vertex *v1 = NULL, Vertex *v2 = NULL);

    /**
     * @brief Edge destructor 
     */
    ~Edge();

    // GETTERS

    /**
     * @brief Retrurns the two vertexes that this edge connects 
     */
    std::pair<Vertex *, Vertex *> getVertexes();

    /**
     * @brief Returns this edge's value 
     */
    unsigned int getValue();

    /**
     * @brief Returns this edge's identifier 
     */
    unsigned int getId();

    // SETTERS

    /**
     * @brief Sets this edge's Id to the provided one
     * @param edge_id The unique identifier given to this edge
     */
    void setId(unsigned int edge_id);

    /**
     * @brief Sets this edge's vertexes
     * @param vertexes Pair containing both vertexes
     */
    void setVertexes(std::pair<Vertex *, Vertex *> vertexes);

    /**
     * @brief Sets this edge's value to the provided one
     * @param edge_value The new value or cost given to this edge 
     */
    void setValue(double edge_value);
};

#endif // EDGE_H
