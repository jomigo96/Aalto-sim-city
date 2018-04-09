#include "MapItem.hpp"
#include "Intersection.hpp"

MapItem::MapItem(Position position, std::list<Road>& roads) : m_position(position) {

	// construct m_adjacent_positions
	int currentX = m_position.getCell().getX();
	int currentY = m_position.getCell().getY();
	std::vector<std::pair<int, int>> orientations;
	// 4 directions: NORTH, EAST, SOUTH, WEST
	orientations.push_back(std::pair<int, int>(0, -1));
	orientations.push_back(std::pair<int, int>(1, 0));
	orientations.push_back(std::pair<int, int>(0, 1));
	orientations.push_back(std::pair<int, int>(-1, 0));
	for (Road road : roads) {
		for (auto orientation : orientations) {
			Position position = Position(Cell(currentX + orientation.first, currentY + orientation.second));
			if (road.contains(position)) {
				m_adjacent_positions.push_back(position);
			}
		}
	}
}

MapItem::~MapItem() {
}

sf::RectangleShape MapItem::getShape() const {
    return m_shape;
}

Position MapItem::getPos()const{
	return m_position;
}

bool MapItem::operator==(const MapItem& other) const {
	return m_position == other.m_position;
}

bool MapItem::hasAdjacentPositions() const {
	return !(m_adjacent_positions.empty());
}

std::list<Position>::iterator MapItem::getAdjacentsPositionsIt() {
	return m_adjacent_positions.begin();
}