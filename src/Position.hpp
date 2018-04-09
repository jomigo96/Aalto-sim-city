#ifndef POSITION_HPP
#define POSITION_HPP

/*!
 * \file Position.hpp
 * \brief Position class
 * 
 * 
 * \author Group 2
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Cell.hpp"




/*!
 * \brief Number of pixels
 */
#define MAP_DIM 1000

/*!
 * \brief Number of rows or columns
 */
#define N 30

/*!
 * \brief Number of pixels of a cell
 */
#define CELL_DIM (MAP_DIM/N)



/*!
 * \class Position
 * \brief Class representing a positon in the map
 *
 *  Holds both information in pixels and grid cells.
 */
class Position {
public:
    /*!
     * \brief Default constructor
     *
     * Default constructor of the Position class.
     */
    Position();
    
    /*!
     * \brief Constructor
     *
     * Constructor of the Position class
     *
     * \param x coordinate
     * \param y coordinate
     */
    Position(int x, int y);
    
    /*!
     * \brief Constructor
     * 
     * Constructor of the Position class
     * 
     * \param coordinates coordinates
     */
    Position(sf::Vector2f coordinates);
    
    /*!
     * \brief Constructor
     * 
     * Constructor of the Position class
     * 
     * \param c Cell coordinates
     */
    Position(const Cell& c);
    
    /*!
     * \brief Destructor
     * 
     * Destructor of the Position class
     */
    virtual ~Position();
    
    /*!
     * \brief Copy assignment
     */
    Position& operator=(const Position& other);
    
    /*!
     * \brief Operator ==
     * 
     * Comparison is made pixel-wise
     */
    bool operator==(const Position& other) const;
    
    /*!
     * \brief Operator !=
     * 
     * Comparison is made pixel-wise
     */
    bool operator!=(const Position& other) const;
    
    /*!
     * \brief Return the cell position
     */
    Cell getCell() const;
    
    /*!
     * \brief Return the x coordinate in pixels
     */
    int getX() const;
    
    /*!
     * \brief Return the y coordinate in pixels
     */
    int getY() const;
    
    /*!
     * \brief Return position vector
     */
    sf::Vector2f getPos()const;
    
    /*!
     * \brief Set the x coordinate
     */
    void setX(int x);
    
    /*!
     * \brief Set the y coordinate
     */
    void setY(int y);
    
    /*!
     * \brief Set a cell position
     */
    void setCell(Cell c);
    
    /*!
     * \brief Check if the point is inside the map
     * 
     * \return Boolean
     */
    bool inMap()const;
    
    /*!
     * \brief Get the weight of the position. Only used for the shortest path algorithm.
     */
    unsigned int getWeight() const;
    
    /*!
     * \brief Set the weight of the position. Only used for the shortest path algorithm.
     * 
     * \param weight Weight to be set
     */
    void setWeight(unsigned int weight);
    
    /*!
     * \brief Return a pointer of a Position which is its predecessor. Only used for the shortest path algorithm.
     * 
     * \return Predecessor
     */
    Position* getPredecessor() const;
    
    /*!
     * \brief Set the predecessor of the position. Only used for the shortest path algorithm.
     * 
     * \param predecessor Predecessor
     */
    void setPredecessor(Position* predecessor);
    
    /*!
     * \brief Output operator
     * 
     * Displays in the format: "[Cell_X,Cell_Y] = Weight" + newline.
     */
    friend std::ostream& operator<<(std::ostream& os, const Position& pos);
    
private:
    sf::Vector2f m_coordinates;
    Cell c_pos;
    unsigned int m_weight=0;
    Position* m_predecessor;
};

/*!
 * \brief Convert pixels to Cell 
 */
Cell vector2Cell(sf::Vector2f coordinates);

// Used for comparison between Positions
/*namespace std {
    template <>
    struct hash<Position>
    {
        size_t operator()(Position const & x) const noexcept
        {
            return (
                    (51 + std::hash<int>()(x.getX())) * 51
                    + std::hash<int>()(x.getY())
                    );
        }
    };
}*/


#endif /* POSITION_HPP */

