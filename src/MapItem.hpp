#ifndef MAPITEM_HPP
#define MAPITEM_HPP
/*!
 * \file MapItem.hpp
 * \brief MapItem class
 * \author Group 2
 */
#include <SFML/Graphics.hpp>
#include <list>
#include "Position.hpp"
#include "Road.hpp"


/*!
 * \class MapItem
 * \brief Base class for map items, except roads.
 * 
 */
class MapItem {
public:
    /*!
     * \brief Constructor
     * 
     * \param position Position of the item
     * \param roads List of roads
     */
    MapItem(Position position, std::list<Road>& roads);
    
    /*!
     * \brief Destructor
     */

    virtual ~MapItem();
    
    /*!
     * \brief Get the item's shape
     */
    sf::RectangleShape getShape() const;

    /*!
     * \brief Get the position
     */
    Position getPos() const;
    
    /*!
     * \brief Compare two MapItem instances
     */
    bool operator==(const MapItem& other) const;
    
    /*!
     * \brief Return true if it is adjacent to a road, false otherwise
     */
    bool hasAdjacentPositions() const;
    
    /*!
     * \brief Return an iterator of all the adjacent positions
     */
    std::list<Position>::iterator getAdjacentsPositionsIt();

protected:
    Position m_position;
    sf::RectangleShape m_shape;
    std::list<Position> m_adjacent_positions;
};

#endif /* MAPITEM_HPP */
