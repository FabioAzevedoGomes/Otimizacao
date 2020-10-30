/**
 * This class models a vertex in a Graph, with some of it's attributes 
 * being designed for more efficient color compatibility checks during 
 * the generation of neighbors
 * 
 * Author: Fábio de Azevedo Gomes 
 */
#ifndef VERTEX_H
#define VERTEX_H

#include "Color.h"

// Forward declaration of color
class Color;

class Vertex
{
private:
    static int vertex_count; // Total number of vertexes generated

    int label;                         // Label given to this vertex
    Color *color;                      // Color given to this vertex
    std::vector<Vertex *> adjacent_to; // Vertexes adjacent to this one

public:
    /**
     * @brief Vertex constructor 
     */
    Vertex();

    /**
     * @brief Vertex destructor 
     */
    ~Vertex();

    // Getters
    Color *getColor();
    int getLabel();
    std::vector<Vertex *> getAdjacency();

    // Setters
    void setColor(Color *color);
    void addAdjacent(Vertex *vertex);

    // Checkers
    bool canUse(Color *color);
};

#endif