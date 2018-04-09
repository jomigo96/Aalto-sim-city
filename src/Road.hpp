#ifndef ROAD_HPP
#define ROAD_HPP


/*!
 * \file Road.hpp
 * \brief Road class
 * \author Group 2
 */
#include "Position.hpp"
#include <cstdlib>
#include <algorithm>

/*!
 * \class Road
 * \brief Holds one segment of Road
 *
 *  Each road is a two lane, but can be one-way or not.
 */
class Road{
	
public:
	/*!
     * \brief Default contructor
     * 
     * Sets everything to zeros
     */
	Road();

	/*!
     * \brief Constructor
     * 
     * \param oneway Boolean which says if it is a one-way road
     * \param s start of the left/bottom lane.
     * \param d destination of the left/bottom lane. 
     * 
     */
	Road(bool oneway ,Position* s, Position* d);
	
	/*!
     * \brief Constructor
     * 
     * This constructor is always called from the simplest one, and checks that the road is possible
     * 
     * Throws logic_error_exception if the road is not possible
     * 
     * \param s1 source of lane 1
     * \param s2 source of lane 2
     * \param d1 destination of lane 1
     * \param d2 destination of lane 2
     */
	Road(Position* s1, Position* s2, Position* d1, Position* d2);
	

	/*!
     * \brief Destructor
     */
	~Road();	
	
	/*!
     * \brief Comparison operator
     */
	bool operator==(const Road& other)const;

	
	/*!
     * \brief Copy assignment
     */
	Road& operator=(const Road& other);
	
	/*!
     * \brief Determines if the road is horizontal
     */
	bool isHorizontal()const;
	
	/*!
     * \brief Return the one-way logical
     */
	bool isoneWay()const;
	


	/*!
     * \brief Minimum x coordinate occupied by the road
     * 
     * Used for displaying
     */
	int getXmin()const;
	
	/*!
     * \brief Minimum y coordinate occupied by the road
     * 
     * Used for displaying
     */
	int getYmin()const;

	
	/*!
     * \brief Return the weight of this road (length in cells)
     */
	unsigned int getWeight()const;
	
	
	
	/*!
     * \brief Get the source of lane 1
     */
	Position* getSource1()const;
	
	/*!
     * \brief Get the source of lane 2
     */
	Position* getSource2()const;
	
	
	/*!
     * \brief Get the destination of lane 1
     */
	Position* getDestination1()const;
	
	/*!
     * \brief Get the destination of lane 2
     */
	Position* getDestination2()const;   	
	
    /*!
     * \brief Return true if the given position belongs to the road
     * 
     * \param position Position to be tested
     */
    bool contains(const Position position) const;
    
private:	
	bool oneWay;
	Position* source_1;
	Position* destination_1;
	Position* source_2;
	Position* destination_2;

	unsigned int weight;
	
};

#endif /* ROAD_HPP */
