#ifndef VEHICLE_HPP
#define VEHICLE_HPP
/*!
 * \file Vehicle.hpp
 * \brief Vehicle class
 * \author Group 2
 */


#include <SFML/Graphics.hpp>
#include <string>
#include "Road.hpp"
#include "Position.hpp"
#include "DijkstraPathSelector.hpp"

/*!
 * \brief Default value for a vehicle's speed
 */
#define BASE_SPEED 200

/*!
 * \class Vehicle
 * \brief Base class for all the vehicle-type objects
 *
 */
class Vehicle {
public:
	/*!
     * \brief Constructor
     * 
     * \param name Name/tag of a vehicle
     * \param speed speed in pixels/sec
     * \param color Color
     * \param position Initial position
     * \param roads List of roads in the map
     * \param intersections List of intersections in the map
     */
    Vehicle(std::string name, int speed, sf::Color color, Position position, std::list<Road>& roads, std::list<Intersection>& intersections);
    
    
    /*!
     * \brief Destructor
     */
    virtual ~Vehicle();
    
    /*!
     * \brief Get name of the vehicle
     */
    std::string getName() const;
    
    
    /*!
     * \brief Get the speed of the vehicle
     */
    int getSpeed() const;
    
    
    
    /*!
     * \brief Get the color of the vehicle
     */
    sf::Color getColor() const;
    
    /*!
     * \brief Set the name of the vehicle
     * 
     * \param name Name to be set
     */
    void setName(std::string name);
    
    
    /*!
     * \brief Set the speed of the vehicle
     * 
     * \param speed Speed in pixels/sec
     */
    void setSpeed(int speed);
    
    
    /*!
     * \brief Set the color of the vehicle
     * 
     * \param color Color to be set
     */
    void setColor(sf::Color color);

	/*!
     * \brief Get the Current position of the vehicle
     */
    Position getPosition() const;
    
    /*!
     * \brief Manually set the positon of the vehicle
     */
    void setPosition(Position& position);
    
    
    /*!
     * \brief Calculate and set shortest path to a position
     * 
     * \param position Destination position
     */
    void goTo(Position& position);
    
    
    /*!
     * \brief Move the vehicle along its path
     * 
     * \param elapsed Time in seconds since last frame
     * 
     * \return Whether the vehicle has reached its destination
     */
    bool updatePosition(float elapsed);
    
    /*!
     * \brief Get the orientation of the vehicle
     * 
     * Integer value: 0=right, 90=down, 180=left, 270=up
     */
    int getOrient(void)const;
    
    /*!
     * \brief Set a path manually
     * 
     * Used for testing purposes
     * 
     * \param path Path to be set
     */
    void setPath(Path path);
    
    /*!
     * \brief Return the path
     */
    Path getPath() const;
    
	/*!
     * \brief Get the next position in the vehicle's path
     * 
     * Used for collision avoidance
     * 
     * Returns a position corresponding to the cell (-1,-1) if the path is empty
     */
    Position getNextPosition();
    
    /*!
     * \brief Get the position after the next one in the vehicles path
     * 
     * Used for collision avoidance
     * 
     * Returns a position corresponding to the cell (-1,-1) if the path doesn't have at least 2 nodes.
     */
    Position getNextNextPosition();
    
	
	
private:
    std::string m_name;
    int m_speed; // in pixels/second
    sf::Color m_color;
    Position m_position;
    std::list<Road>& m_roads;
    std::list<Intersection>& m_intersections;
    Path m_path;
    int orientation; //0-right, 90-down, 180-left, 270-up
};

#endif /* VEHICLE_HPP */

