#include "Building.hpp"

Building::Building(Position position, std::list<Road>& roads) : MapItem(position, roads) {
	m_shape = sf::RectangleShape(sf::Vector2f(CELL_DIM, CELL_DIM));
	m_shape.setFillColor(sf::Color::Yellow);
	m_shape.setPosition(position.getPos());
}

Building::~Building() {
}

