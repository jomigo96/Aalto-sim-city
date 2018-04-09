#include "DijkstraPathSelector.hpp"
#include "Intersection.hpp"
#include <iostream>

DijkstraPathSelector::DijkstraPathSelector(Position* src, Position* dst, std::list<Road>& roads, std::list<Intersection>& intersections)
: PathSelector(src, dst, roads, intersections) {
	init();
	process();
	createPath();
}

DijkstraPathSelector::~DijkstraPathSelector() {}

void DijkstraPathSelector::init() {

	// Build graph with roads
	for (Road& road : m_roads) {
		createArcs(road);
	}
	
	// Complete graph with intersections
	for (Intersection& intersection : m_intersections) {
		createArcs(intersection);
	}
	
	// Retrieve all the nodes
	for (Arc arc : m_arcs) {
		Position* pos = arc.src;
		m_positions.insert(std::pair<std::pair<int,int>, Position*>(std::pair<int,int>(pos->getCell().getX(), pos->getCell().getY()), pos));
		pos = arc.dst;
		m_positions.insert(std::pair<std::pair<int,int>, Position*>(std::pair<int,int>(pos->getCell().getX(), pos->getCell().getY()), pos));
	}

	std::map<std::pair<int,int>, Position*>::iterator it;
	
	// Initialization of the weight of each node
	for (it = m_positions.begin(); it != m_positions.end(); it++) {
		if (*(it->second) == *m_source) {
			it->second->setWeight(0);
		} else {
			it->second->setWeight(UINT_MAX);
		}
	}
		
}

// Create arcs using a road
void DijkstraPathSelector::createArcs(Road& road) {
	Position* src1 = road.getSource1();
	Position* dst1 = road.getDestination1();
	Position* src2 = road.getSource2();
	Position* dst2 = road.getDestination2();
	unsigned int weight = road.getWeight();
	addArcs(src1, dst1, weight, false);
	addArcs(src2, dst2, weight, false);
}

// Create arcs within an intersection
void DijkstraPathSelector::createArcs(Intersection& intersection) {
	int x = intersection.getPos().getCell().getX();
	int y = intersection.getPos().getCell().getY();
	std::vector<std::pair<int, int>> orientations;
	// List of all the positions which are adjacent to an intersection
	orientations.push_back(std::pair<int, int>(x-1, y+0));
	orientations.push_back(std::pair<int, int>(x+0, y-1));
	orientations.push_back(std::pair<int, int>(x+1, y-1));
	orientations.push_back(std::pair<int, int>(x+2, y+0));
	orientations.push_back(std::pair<int, int>(x+2, y+1));
	orientations.push_back(std::pair<int, int>(x+1, y+2));
	orientations.push_back(std::pair<int, int>(x+0, y+2));
	orientations.push_back(std::pair<int, int>(x-1, y+1));
	for (auto pair1 : orientations) {
		int src_x = pair1.first;
		int src_y = pair1.second;
		Position* src = new Position(Cell(src_x, src_y)); // source node has to be a destination in its road
		if (isDestination(src)) {
			for (auto pair2 : orientations) {
				int dst_x = pair2.first;
				int dst_y = pair2.second;
				Position* dst = new Position(Cell(dst_x, dst_y)); // destination node has to be a source in its road
				if (isSource(dst) && !inSameRoad(src, dst)) {
					addArcs(src, dst, getWeight(src, dst), true);
				}
			}
		}
	}
}

// true if two side by side positions belongs to a same road
bool DijkstraPathSelector::inSameRoad(Position* src, Position* dst) {
	for (Road& road : m_roads) {
		if ((*road.getDestination2() == *src && *road.getSource1() == *dst)
				|| (*road.getDestination1() == *src && *road.getSource2() == *dst)) {
			return true;
		}
	}
	return false;
}


// true if the position is a source in its road
bool DijkstraPathSelector::isSource(Position* pos) {
	for (Road& road : m_roads) {
		if (*road.getSource1() == *pos || *road.getSource2() == *pos) {
			return true;
		}
	}
	return false;
}

// true if the position is a destination in its road
bool DijkstraPathSelector::isDestination(Position* pos) {
	for (Road& road : m_roads) {
		if (*road.getDestination1() == *pos || *road.getDestination2() == *pos) {
			return true;
		}
	}
	return false;
}

// Build arcs between src and dst
void DijkstraPathSelector::addArcs(Position* src, Position* dst, unsigned int weight, bool intersection) {
	
	int x_src, y_src, x_dst, y_dst, x_min, x_max, y_min, y_max;
	unsigned int arc_weight;
	x_src = src->getCell().getX();
	y_src = src->getCell().getY();
	x_dst = dst->getCell().getX();
	y_dst = dst->getCell().getY();
	
	x_min = (x_src < x_dst) ? x_src : x_dst;
	y_min = (y_src < y_dst) ? y_src : y_dst;
	x_max = (x_src > x_dst) ? x_src : x_dst;
	y_max = (y_src > y_dst) ? y_src : y_dst;
	
	if (x_min == x_max) { // vertical
		arc_weight = weight/(y_max - y_min);
		if (intersection) { // no intermediate arc if it corresponds to an intersection
			addArc(src, dst, arc_weight);
		} else if (y_src == y_min) { // else, create intermediate arcs
			for (int y = y_src; y < y_dst; y++) {
				Position* src = new Position(Cell(x_min, y));
				Position* dst = new Position(Cell(x_min, y + 1));
				addArc(src, dst, arc_weight);
			}
		} else {
			for (int y = y_src; y > y_dst; y--) {
				Position* src = new Position(Cell(x_min, y));
				Position* dst = new Position(Cell(x_min, y - 1));
				addArc(src, dst, arc_weight);
			}
		}
	} else if (y_min == y_max) { // horizontal
		arc_weight = weight/(x_max - x_min);
		if (intersection) {
			addArc(src, dst, arc_weight);
		} else if (x_src == x_min) {
			for (int x = x_src; x < x_dst; x++) {
				Position* src = new Position(Cell(x, y_min));
				Position* dst = new Position(Cell(x + 1, y_min));
				addArc(src, dst, arc_weight);
			}
		} else {
			for (int x = x_src; x > x_dst; x--) {
				Position* src = new Position(Cell(x, y_min));
				Position* dst = new Position(Cell(x - 1, y_min));
				addArc(src, dst, arc_weight);
			}
		}
	} else if (intersection) {
		Position* between = getBetween(src, dst);
		addArc(src, between, getWeight(src, between));
		addArc(between, dst, getWeight(between, dst));
	}
	
}

// Return the position which is inside an intersection (intermediate node within an intersection)
Position* DijkstraPathSelector::getBetween(Position* src, Position *dst) {
	Position* p1 = new Position(Cell(src->getCell().getX(), dst->getCell().getY()));
	Position* p2 = new Position(Cell(dst->getCell().getX(), src->getCell().getY()));
	for (Intersection intersection : m_intersections) {
		if (intersection.contains(*p1)) {
			return p1;
		} else if (intersection.contains(*p2)) {
			return p2;
		}
	}
	return nullptr;
}

// Add arc to the graph
void DijkstraPathSelector::addArc(Position* src, Position* dst, unsigned int weight) {
	if (*src == *dst) {
		return;
	}
	Arc arc;
	arc.src = src;
	arc.dst = dst;
	arc.weight = weight;
	if (!arcExists(src, dst)) {
		m_arcs.push_back(arc);
	}
}

Arc DijkstraPathSelector::getArc(Position* src, Position* dst) {
	for (Arc arc : m_arcs) {
		if (*arc.src == *src && *arc.dst == *dst) {
			return arc;
		}
	}
}

bool DijkstraPathSelector::arcExists(Position* src, Position* dst) {
	for (Arc arc : m_arcs) {
		if (*arc.src == *src && *arc.dst == *dst) {
			return true;
		}
	}
	return false;
}


// Calculate the weight between two positions, even if there are not aligned
unsigned int DijkstraPathSelector::getWeight(Position* src, Position* dst) {
	return abs(dst->getCell().getX() - src->getCell().getX()) + abs(dst->getCell().getY() - src->getCell().getY());
}


// Return the node with the lowest weight
Position* DijkstraPathSelector::getMin() {
	
	unsigned int minWeight = UINT_MAX;
	std::map<std::pair<int,int>, Position*>::iterator it;
	Position* minPos = nullptr;
	
	for (it = m_positions.begin(); it != m_positions.end(); it++) {
		Position* pos = it->second;
		if (pos->getWeight() < minWeight) {
			minWeight = pos->getWeight();
			minPos = pos;
		}
	}

	return minPos;
}

// Update weights and predecessor
void DijkstraPathSelector::update(Position* p1, Position* p2, unsigned int arcWeight) {
	if (p2->getWeight() > p1->getWeight() + arcWeight) {
		p2->setWeight(p1->getWeight() + arcWeight);
		p2->setPredecessor(p1);
	}
}

// General algorithm
void DijkstraPathSelector::process() {

	std::map<std::pair<int,int>, Position*>::iterator it;
	
	while (!m_positions.empty()) {
		Position* minPos = getMin();
		if (!minPos) { // minimum not found
			return;
		}
		m_positions.erase(std::pair<int,int>(minPos->getCell().getX(), minPos->getCell().getY()));
		
		for (Arc arc : m_arcs) {
			Position* src = arc.src;
			Position* dst = arc.dst;
			if (*src == *minPos) {
				for (it = m_positions.begin(); it != m_positions.end(); it++) {
					Position* pos = it->second;
					if (*pos == *dst) {
						update(minPos, pos, arc.weight);
					}
				}
			}
		}
	}
	
}

// Create path if possible
void DijkstraPathSelector::createPath() {
	Position* pos;

	for (Arc arc : m_arcs) {
		if (*arc.dst == *m_destination) {
			pos = arc.dst;
			m_destination = arc.dst;
		}
		if (*arc.src == *m_source) {
			m_source = arc.src;
		}
	}
	
	if (m_destination->getWeight() == UINT_MAX) {
		// no path
		return;
	}
	
	while (*pos != *m_source) {
		m_path.addNode(pos);
		pos = pos->getPredecessor();
	}
	m_path.addNode(m_source);
}
