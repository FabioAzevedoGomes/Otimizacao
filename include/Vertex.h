#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "Color.h"

class Color;

class Vertex
{
private:
    // Vertex unique identifier
    unsigned int id;

    // Color assigned to vertex
    unsigned int color;

    // Vertexes that are adjacent to vertex
    std::vector<unsigned int> adjacency_list;

public:
    /**
     * @brief Vertex constructor
     */
    Vertex(unsigned int vertex_id = -1, unsigned int color_id = -1);

    /**
     * @brief Class destructor 
     */
    ~Vertex();

    /**
     * @brief Returns the adjacency list for this vertex 
     * @returns std::vector containing every vertex adjacent to this
     */
    std::vector<unsigned int> getAdjacent();

    // SETTERS

    /**
     * @brief Inserts a new vertex and adjacent
     */
    void setAdjacent(unsigned int vertex_id);

    /**
     * @brief Labels this vertex with given id 
     */
    void setId(unsigned int vertex_id);

    /**
     * @brief Gives the provided color to the vertex, if it can receive it
     * @param color The color given to this vertex 
     */
    void setColor(unsigned int color_id);

    // GETTERS

    /**
     * @brief Returns this vertex's color 
     */
    unsigned int getColor();

    /**
     * @brief Returns this vertex's identifier 
     */
    unsigned int getId();

    // CHECKERS

    /**
     * @brief Checks if this vertex is adjacent to given vertex
     * @param vertex_id
     */
    bool isAdjacentTo(unsigned int vertex_id);

};

#endif //VERTEX_H
