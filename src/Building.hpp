#ifndef BUILDING_HPP
#define BUILDING_HPP

/*!
 * \file Building.hpp
 * \brief Building class
 * \author Group 2
 */

#include "MapItem.hpp"

/*!
 * \class Building
 * \brief Basic class representing a building
 */
class Building : public MapItem {
public:
    /*!
     * \brief Constructor
     */
    Building(Position position, std::list<Road>& roads);
    
    /*!
     * \brief Destructor
     */
    virtual ~Building();
private:

};

#endif /* BUILDING_HPP */

