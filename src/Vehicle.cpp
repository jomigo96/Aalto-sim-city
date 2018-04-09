#include "Vehicle.hpp"

Vehicle::Vehicle(std::string name, int speed, sf::Color color, Position position, std::list<Road>& roads, std::list<Intersection>& intersections)
: m_name(name), m_speed(speed), m_color(color), m_position(position), m_roads(roads), m_intersections(intersections) {
	
	orientation=0;

}

Vehicle::~Vehicle() {
}

std::string Vehicle::getName() const {
    return m_name;
}

int Vehicle::getSpeed() const {
    return m_speed;
}

sf::Color Vehicle::getColor() const {
    return m_color;
}

void Vehicle::setName(std::string name) {
    m_name = name;
}

void Vehicle::setSpeed(int speed) {
    m_speed = speed;
}

void Vehicle::setColor(sf::Color color) {
    m_color = color;
}


Position Vehicle::getPosition() const {
	return m_position;
}

void Vehicle::setPosition(Position& position) {
	m_position = position;
}

void Vehicle::goTo(Position& position) {
	DijkstraPathSelector dij(&this->m_position, &position, m_roads, m_intersections);
	m_path = dij.getPath();
}

bool Vehicle::updatePosition(float elapsed) {
	
	if (m_path.isEmpty()) {
		return true;
	}
	
	Position* next = m_path.nextNode();
	
	if (m_position == *next) {
		m_path.removeCurrentNode();
		next = m_path.nextNode();
	}
	
	if (m_path.isEmpty()) {
		return true;
	}
	
	//Cell previous_pos=m_position.getCell();
	int currentX = m_position.getX();
	int currentY = m_position.getY();
	int nextX = next->getX();
	int nextY = next->getY();
	int diffX = nextX - currentX;
	int diffY = nextY - currentY;
	int deltaX = 0;
	int deltaY = 0;
	
	if (diffX > 0) {
		deltaX = (int) m_speed*elapsed;
		orientation=0;
	} else if (diffX < 0) {
		deltaX = (int)-m_speed*elapsed;
		orientation=180;
	}
	
	if (diffY > 0) {
		deltaY = (int) m_speed*elapsed;
		orientation=90;
	} else if (diffY < 0) {
		deltaY = (int)-m_speed*elapsed;
		orientation=270;
	}
	
	// prevent the vehicle from exceeding the position of the destination
	if (abs(deltaX) > abs(diffX)) {
		deltaX = diffX;
	}
	if (abs(deltaY) > abs(diffY)) {
		deltaY = diffY;
	}
	
	Position newPos(currentX + deltaX, currentY + deltaY);
	this->setPosition(newPos);
	
	/*//Remove current node if it is already reached, exept in corners
	if((newPos.getCell()==next->getCell())&&(m_path.getSize()>1)){
		m_path.removeCurrentNode();
	}*/
}

void Vehicle::setPath(Path path) {

	m_path=path;
}

Path Vehicle::getPath() const {
	return m_path;
}

int Vehicle::getOrient(void)const{
	
	return orientation;
}

Position Vehicle::getNextPosition(){
	
	if (m_path.isEmpty()) {
		return Position(Cell(-1,-1));
	}
	Position* next = m_path.nextNode();
	
	return *next;
}

Position Vehicle::getNextNextPosition(){
	
	if (m_path.getSize()<2)
		return Position(Cell(-1,-1));
		
	Position* next=m_path.nextNode();
	
	m_path.removeCurrentNode();
	
	Position* nextnext=m_path.nextNode();
	
	m_path.addNode(next);
	
	return *nextnext;
	
}
