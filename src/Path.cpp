#include "Path.hpp"
#include <iostream>

Path::Path() {
	
}

Path::Path(Position* src, Position* dst) : m_source(src), m_destination(dst) {
}

Path::~Path() {
}

void Path::addNode(Position* pos) {
	m_path.push(pos);
}

void Path::print() const {
	std::cout << "From " << *m_source << "to " << *m_destination;
	for (std::stack<Position*> dump = m_path; !dump.empty(); dump.pop()) {
		std::cout << *dump.top();
	}
}

Position* Path::nextNode() {
	return m_path.top();
}

void Path::removeCurrentNode() {
	m_path.pop();
}

bool Path::isEmpty() const {
	return m_path.empty();
}

int Path::getSize() const {
	return m_path.size();
}

/*std::ostream& operator<<(std::ostream& out, Path path){
	
	Position* p;
	
	out<< "Path nodes:"<<std::endl;
	
	while(!path.isEmpty()){
		
		p=path.m_path.top();
		path.m_path.pop();
		out << "Node: (x,y)=("<<p->getCell().getX()<<","<<p->getCell().getY()<<")"<<std::endl;
		
	}
	out<<"End of path."<<std::endl;
	return out;
}*/
