#ifndef PATHSELECTOR_HPP
#define PATHSELECTOR_HPP
/*!
 * \file PathSelector.hpp
 * \brief PathSelector class
 * \author Group 2
 */


#include <climits>
#include <list>
#include <algorithm>
#include "Position.hpp"
#include "Path.hpp"
#include "Road.hpp"
#include "Intersection.hpp"

/*!
 * \class PathSelector
 * 
 * \brief Contains different algorithms to define a path
 */
class PathSelector {
public:
	/*!
     * \brief Constructor
     * 
     * \param src Source position pointer
     * \param dest Destination position pointer
     * \param roads List of roads
     * \param intersections List of intersections
     */
    PathSelector(Position* src, Position* dest, std::list<Road>& roads, std::list<Intersection>& intersections);
    
    /*!
     * \brief Destructor
     */
    virtual ~PathSelector();
    
    /*!
     * \brief Return the path
     */
    Path getPath() const;
protected:
    Position* m_source;
    Position* m_destination;
    Path m_path;
    std::list<Road>& m_roads;
    std::list<Intersection>& m_intersections;
};

#endif /* PATHSELECTOR_HPP */

