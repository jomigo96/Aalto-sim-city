#include "Parking.hpp"

Parking::Parking(Position position, std::list<Road>& roads, std::list<Intersection>& intersections, int creationTime)
: MapItem(position, roads), m_roads(roads), m_intersections(intersections), m_creation_time(creationTime) {
	m_shape = sf::RectangleShape(sf::Vector2f(CELL_DIM, CELL_DIM));
	m_shape.setFillColor(sf::Color::Cyan);
	m_shape.setPosition(position.getPos());
}

Parking::~Parking() {
}

Car* Parking::createCar(const int elapsed, std::vector<Vehicle*> vehicles) {
	if (!this->hasAdjacentPositions()) {
		return nullptr;
	}
	
	// retrieve the first position
	Position spawningPos = m_adjacent_positions.front();

	//Check that the spawning position is free
	for (Vehicle* vehicle : vehicles){
		
		if(vehicle->getPosition().getCell() == spawningPos.getCell())
			return nullptr;
		
	}


	if (m_creation_time + m_generated_cars * m_time_interval <= elapsed) {
		Car* car = new Car("generated", 200, sf::Color::Blue, Position(spawningPos.getCell()), m_roads, m_intersections);
		m_generated_cars++;
		return car;
	}
	
	return nullptr;
}
