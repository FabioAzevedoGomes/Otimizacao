#ifndef COLOR_H
#define COLOR_H

#include <vector>

#include "Vertex.h"

class Vertex;

class Color
{
private:
    // Unique identifier given to this color
    unsigned int id;

    // Set of vertexes that use this color
    std::vector<unsigned int> used_by;

public:
    /**
     * @brief Color constructor 
     */
    Color(unsigned int color_id = 0);

    /**
     * @brief Color destructor 
     */
    ~Color();

    // GETTERS

    /**
     * @brief Returns this color's unique identifier
     */
    unsigned int getId();

    /**
     * @brief Returns this color's list of users 
     */
    std::vector<unsigned int> getUsers();

    /**
     * @brief Returns the amount of vertexes that
     * use this color 
     */
    unsigned int getUsageCounter();

    // SETTERS

    /**
     * @brief Sets this color's unique identifier 
     * @param color_id Color id
     */
    void setId(unsigned int color_id);

    /**
     * @brief Adds a new vertex as using this color
     */
    void addUser(unsigned int vertex_id);

    /**
     * @brief Removes a vertex as using this color
     */
    void removeUser(unsigned int vertex);
};

#endif // COLOR_H
