#ifndef DIJKSTRAPATHSELECTOR_HPP
#define DIJKSTRAPATHSELECTOR_HPP

/*!
 * \file DijkstraPathSelector.hpp
 * \brief DijkstraPathSelector class
 * \author Group 2
 */

#include <memory>
#include <vector>
#include "PathSelector.hpp"

/*!
 * \brief Structure representing an arc
 */
struct Arc {
    Position* src; /*!< Source node */
    Position* dst; /*!< Destination node */
    unsigned int weight; /*!< Weight of the arc */
};

/*!
 * \class DijkstraPathSelector
 * \brief Implementation of Dijkstra's shortest path algorithm
 *
 *  This class is used for the calculation of the shortest path for a vehicle
 */
class DijkstraPathSelector : public PathSelector {
public:
    /*!
     * \brief Constructor
     * 
     * \param src Source position
     * \param dst Destination position
     * \param roads List of roads
     * \param intersections List of intersections
     */
    DijkstraPathSelector(Position* src, Position* dst, std::list<Road>& roads, std::list<Intersection>& intersections);
    
    /*!
     * \brief Destructor
     */
    virtual ~DijkstraPathSelector();
private:
    void init();
    Position* getMin();
    void update(Position* p1, Position* p2, unsigned int arcWeight);
    void process();
    void createPath();
    void createArcs(Road& road);
    void createArcs(Intersection& intersection);
    bool inSameRoad(Position* src, Position* dst);
    bool isSource(Position* pos);
    bool isDestination(Position* pos);
    Position* getBetween(Position* src, Position *dst);
    void addArcs(Position* src, Position* dst, unsigned int weight, bool intersection);
    void addArc(Position* src, Position* dst, unsigned int weight);
    bool arcExists(Position* src, Position* dst);
    Arc getArc(Position* src, Position* dst);
    static unsigned int getWeight(Position* src, Position* dst);
    std::map<std::pair<int,int>, Position*> m_positions;
    std::vector<Arc> m_arcs;
};

#endif /* DIJKSTRAPATHSELECTOR_HPP */

