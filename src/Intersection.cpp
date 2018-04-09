#include "Intersection.hpp"

Intersection::Intersection(Position pos, std::list<Road>& roads) : MapItem(pos, roads) {
	way=right;
}

	
Intersection::~Intersection(){}
	

Intersection& Intersection::operator=(const Intersection& other){
	
	this->m_position=other.getPos();	
	return *this;
}
	
void Intersection::toggle(){

	switch (way){
		
		case right: way=down; break;
		case down: way=left; break;
		case left: way=top; break;
		case top: way=right; break;
		
	}
}
	
Way Intersection::getWay()const{

	return way;
}

bool Intersection::contains(const Position pos) const {
	int x = pos.getCell().getX();
	int y = pos.getCell().getY();
	int this_x = m_position.getCell().getX();
	int this_y = m_position.getCell().getY();
	int x_min = this_x, x_max = this_x + 1, y_min = this_y, y_max = this_y + 1;
	bool between_x = false;
	bool between_y = false;
	between_x = (x_min <= x) && (x <= x_max);
	between_y = (y_min <= y) && (y <= y_max);
	return between_x && between_y;
}