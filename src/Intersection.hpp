#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP
/*!
 * \file Intersection.hpp
 * \brief Intersection class
 * \author Group 2
 */


#include "MapItem.hpp"
#include "Position.hpp"


/*!
 * \brief Base time to toggle the traffic lights
 */
#define INTERSECTION_TIME 3


/*!
 * \brief The directions connected to an intersection
 */
enum Way{
	
	right,
	down,
	left, 
	top
};

/*!
 * \class Intersection
 * \brief Class representing an intersection of roads
 * 
 * An intersection is to be placed in the end of a road, and contains traffic lights that coordinate traffic flow.
 * 
 * Each intersection occupies 4 squares, and its position is the top-left one.
 *
 */
class Intersection : public MapItem{


public:	
	/*!
     * \brief "Default" constructor
     * 
     * \param pos Top-left position of the intersection
     * \param roads List of roads
     */
	Intersection(Position pos, std::list<Road>& roads);
	
	/*!
     * \brief Destructor
     */
	~Intersection();
	
	/*!
     * \brief Copy assignment
     */
	Intersection& operator=(const Intersection& other);
	
	/*!
     * \brief Toggles the traffic lights, clockwise.
     */
	void toggle();
	
	/*!
     * \brief Get the direction whose traffic light is green.
     */
	Way getWay()const;
    
    /*!
     * \brief Check if the intersection contains a given position
     * 
     * \param pos Position to be tested
     * 
     * \return Boolean value
     */
    bool contains(const Position pos) const;
	
private:
	
	Way way;
};

#endif
