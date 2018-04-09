#ifndef CAR_HPP
#define CAR_HPP

/*!
 * \file Car.hpp
 * \brief Car class
 * 
 * 
 * \author Group 2
 */

#include "Vehicle.hpp"


/*!
 * \class Car
 * \brief Type of vehicle
 *
 */
class Car : public Vehicle {
public:
	/*!
     * \brief Constructor
     *
     * \param name Name/tag of the car
     * \param speed Speed in pixels/sec
     * \param color Color
     * \param position Initial position
     * \param roads list of roads in the map
     * \param intersections list of intersections in the map
     */
    Car(std::string name, int speed, sf::Color color, Position position, std::list<Road>& roads, std::list<Intersection>& intersections);
    
    /*!
     * \brief Destructor 
     * 
     */
    virtual ~Car();
private:

};

#endif /* CAR_HPP */

