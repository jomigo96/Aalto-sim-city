#include "Position.hpp"

Position::Position() {
    m_coordinates.x = 0;
    m_coordinates.y = 0;
    c_pos=Cell(0,0);
}

Position::Position(int x, int y) {
	
    m_coordinates = sf::Vector2f(x,y);
    c_pos=vector2Cell(m_coordinates);
}

Position::Position(sf::Vector2f coordinates) : m_coordinates(coordinates) {
	
	c_pos=vector2Cell(coordinates);
}

Position::Position(const Cell& c) : c_pos(c){
	
	m_coordinates.x=c.getX()*CELL_DIM;
	m_coordinates.y=c.getY()*CELL_DIM;
}

Position::~Position() {
}

int Position::getX() const {
    return (int) m_coordinates.x;
}

int Position::getY() const {
    return (int) m_coordinates.y;
}

void Position::setX(int x) {
    m_coordinates.x = x;
    c_pos=vector2Cell(m_coordinates);
}

void Position::setY(int y) {
    m_coordinates.y = y;
    c_pos=vector2Cell(m_coordinates);
}

Position& Position::operator=(const Position& other){
	
	this->m_coordinates=other.getPos();
	this->c_pos=other.getCell();
	
	return *this;
}

bool Position::operator==(const Position& other) const {
    return other.m_coordinates == this->m_coordinates;
}

bool Position::operator!=(const Position& other) const{

	return !(*this==other);
}


Cell Position::getCell() const{

	return c_pos;
}

void Position::setCell(Cell c){
	
	c_pos=c;
	
	m_coordinates.x=c.getX()*CELL_DIM;
	m_coordinates.y=c.getY()*CELL_DIM;
}

bool Position::inMap()const{
	
	return !((c_pos.getX()<0)||(c_pos.getX()>=MAP_DIM)||(c_pos.getY()<0)||(c_pos.getY()>=MAP_DIM));
}



Cell vector2Cell(sf::Vector2f coordinates){
	
	return Cell((int)coordinates.x/CELL_DIM, (int)coordinates.y/CELL_DIM);
}


sf::Vector2f Position::getPos()const{
	
	return m_coordinates;
}

unsigned int Position::getWeight() const {
	return m_weight;
}

void Position::setWeight(unsigned int weight) {
	m_weight = weight;
}

Position* Position::getPredecessor() const {
	return m_predecessor;
}

void Position::setPredecessor(Position* predecessor) {
	m_predecessor = predecessor;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {  
    os << "[" << pos.getCell().getX() << "," << pos.getCell().getY() << "] = " << pos.getWeight() << std::endl;
    return os;  
}  
