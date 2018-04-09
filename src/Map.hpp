#ifndef MAP_HPP
#define MAP_HPP

/*!
 * \file Map.hpp
 * \brief Map class
 * \author Group 2
 */
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include <functional>
#include "MapItem.hpp"
#include "Position.hpp"
#include "Vehicle.hpp"
#include "Road.hpp"
#include "Intersection.hpp"
#include "Parking.hpp"
#include "Building.hpp"

/*!
 * \class Map
 * \brief Class representing the map
 *
 *  This class contains all the buildings, vehicles and roads.
 *  This class is responsible for the movement and spawning of vehicles.
 */
class Map {
public:
    /*!
     *  \brief Constructor
     *
     *  Constructor of the Map class
     *
     *  \param texture texture displayed
     */
    Map(sf::RenderTexture& texture);
    
    /*!
     * \brief Destructor
     * 
     * Destructor of the Map class
     */
    virtual ~Map();
    
    /*!
     * \brief Clear the map
     * 
     * Clear the map
     */
    void clear();
    
    /*!
     * \brief Draw a black grid
     * 
     * Draw a black grid
     */
    void drawGrid();
    
    /*!
     * \brief Return the map sprite
     * 
     * Return the map sprite
     */
    sf::Sprite getSprite() const;
    
    /*!
     * \brief Add a vehicle
     * 
     * \param vehicle Pointer to the vehicle to be added
     */
    void addVehicle(Vehicle* vehicle);
    
    /*!
     * \brief Draw the map and its content in the window
     * 
     * \param window SFML render window reference
     */
    void draw(sf::RenderWindow& window) const;
    
    /*!
     * \brief Set the road texture
     * 
     * \param tex Road texture
     */
    void setRoadTexture(const sf::Texture& tex);
    
    /*!
     * \brief Set the intersection texture
     * 
     * \param tex Intersection texture
     */
    void setIntersectionTexture(const sf::Texture& tex);
    
    /*!
     * \brief Set the car texture
     * 
     * \param tex Car texture
     */
    void setCarTexture(const sf::Texture& tex);
    
    /*!
     * \brief Add a road to the registry
     * 
     * \param r Road to be added
     * 
     * \return Whether insertion was successful
     */
    bool addRoute(const Road& r);
    
    /*!
     * \brief Add an intersection to the registry
     * 
     * \param i Intersection to be added
     * 
     * \return Whether insertion was successful
     */
    bool addIntersection(const Intersection& i);
    
    /*!
     * \brief Return a reference to the list of Intersections
     * 
     * 
     */
    std::list<Intersection>& getIntersections();

    
    /*!
     * \brief Return a reference to the list of Routes
     * 
     */
    std::list<Road>& getRoutes();
    
    /*!
     * \brief Remove an intersection from the list
     * 
     * \param intersection Intersection to be removed
     */
    void removeIntersection(Intersection intersection);
    
    /*!
     * \brief Remove a route from the list
     * 
     * \param r Route to be removed
     */
    void removeRoute(Road r);
    
    /*!
     * \brief Remove a route from the list
     * 
     * \param p Position through which the route passes
     */
    void removeRoute(Position p);

	/*!
     * \brief update vehicle positions for this frame
     * 
     * \param elapsed Time since the previous frame
     */
	void stepPositions(const float elapsed);
	
	/*!
     * \brief Change all traffic lights
     * 
     */
	void toggleIntersections();
	
	/*!
     * \brief Test if Position is an end node of a Road
     * 
     * \param pos Position object to test
     * 
     * \return Boolean
     */
	bool atEndofRoad(Position pos)const;
	
    /*!
     * \brief Add a parking to the map
     * 
     * \param parking Pointer to the Parking to be added
     */
	void addParking(Parking* parking);
    
    /*!
     * \brief Remove a parking from the map
     * 
     * \param parking pointer to Parking to be removed
     */
    void removeParking(Parking* parking);
    
    /*!
     * \brief Generate cars from parkings
     */
    void generateTraffic();
    
    /*!
     * \brief Set the elapsed time since the beginning of the simulation
     * 
     * \param elapsed Elapsed time
     */
    void setElapsedTime(const int elapsed);
    
    /*!
     * \brief Return the elapsed time
     */
    int getElapsedTime() const;
    
    /*!
     * \brief Add a building to the map
     * 
     * \param building Building to be added
     */
	void addBuilding(Building building);
    
    /*!
     * \brief Remove a building from the map
     * 
     * \param building Building to be removed
     */
    void removeBuilding(Building building);
    
    /*!
     * \brief Change the speed of all the vehicles
     * 
     * \param speed Speed of a vehicle
     */
    void changeSpeeds(const int speed);
    
    /*!
     * \brief Return the list of parkings
     */
    std::list<Parking*>& getParkings();
    
    /*!
     * \brief Return the list of buildings
     */
    std::list<Building>& getBuildings();
    
    
    /*!
     * \brief Check if a cell is occupied with anything
     */
    bool isOccupied(Cell c)const;
    
private:
	Position* findDestination(Position source) const;
    
    sf::RenderTexture& m_texture;
    std::vector<Vehicle*> m_vehicles;
    std::list<Road> m_routes;
    std::list<Intersection> m_intersections;
    std::list<Parking*> m_parkings;
    std::list<Building> m_buildings;
    sf::Texture int_texture;
    sf::Texture road_texture;
    sf::Texture car_texture;
    int m_elapsed = 0;
    
    /*!
     * \brief Get intersection linked to a Road end node.
     * 
     * This should only be called after atEndofRoad.
     * 
     * \param pos Position object of the end node.
     * 
     * \return Intersection object
     */
    Intersection whichIntersection(Position pos)const;
};

#endif /* MAP_HPP */

