#ifndef PARKING_HPP
#define PARKING_HPP
/*!
 * \file Parking.hpp
 * \brief Parking class
 * \author Group 2
 */

#include "MapItem.hpp"
#include "Car.hpp"
#include <iostream>
#include <stdlib.h>

/*!
 * \brief Time interval between the spawning of two consecutive cars
 */
#define DEFAULT_TIME_INTERVAL 20

/*!
 * \class Parking
 * \brief Building responsible for spawning and despawning vehicles.
 */
class Parking : public MapItem {
public:

    /*!
     * \brief Constructor
     * 
     * \param position Parking position
     * \param roads list of roads
     * \param intersection list of intersections
     * \param creationTime Time when the parking was created
     */
    Parking(Position position, std::list<Road>& roads, std::list<Intersection>& intersection, int creationTime);
    
    /*!
     * \brief Destructor
     */

    virtual ~Parking();
    
    /*!
     * \brief Spawn a car
     * 
     * \param elapsed time since last spawn
     * \param vehicles List of vehicles
     * 
     * \return Pointer to the new car object
     */
    Car* createCar(const int elapsed, std::vector<Vehicle*> vehicles);
    
private:
    Position getSpawningPosition() const;
    int m_time_interval = DEFAULT_TIME_INTERVAL;
    int m_creation_time = 0;
    int m_generated_cars = 0;
    bool m_spawnable = false;
    std::list<Road> m_roads;
    std::list<Intersection> m_intersections;
};

#endif /* PARKING_HPP */

