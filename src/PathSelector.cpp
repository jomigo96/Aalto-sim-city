#include "PathSelector.hpp"

PathSelector::PathSelector(Position* src, Position* dest, std::list<Road>& roads, std::list<Intersection>& intersections)
: m_source(src), m_destination(dest), m_roads(roads), m_path(src, dest), m_intersections(intersections) {

}

PathSelector::~PathSelector() {
}

Path PathSelector::getPath() const {
	return m_path;
}