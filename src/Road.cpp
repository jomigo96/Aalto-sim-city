#include "Road.hpp"

Road::Road(){
	
	source_1= nullptr;
	source_2= nullptr;
	destination_1= nullptr;
	destination_2= nullptr;
	oneWay=true;
	weight=0;
}

Road::Road(bool oneway, Position* s, Position* d){
	
	Position* s2 = new Position();
	Position* d2 = new Position();
	Cell c;
	
	if(oneway){
		if(s->getCell().getX()==d->getCell().getX()){
			c=Cell(s->getCell().getX()+1, s->getCell().getY());
			s2->setCell(c);
			c=Cell(d->getCell().getX()+1, d->getCell().getY());
			d2->setCell(c);
		}else{
			c=Cell(s->getCell().getX(), s->getCell().getY()-1);
			s2->setCell(c);
			c=Cell(d->getCell().getX(), d->getCell().getY()-1);
			d2->setCell(c);
		}		
	}else{
		if(s->getCell().getX()==d->getCell().getX()){
			c=Cell(d->getCell().getX()+1, d->getCell().getY());
			s2->setCell(c);
			c=Cell(s->getCell().getX()+1, s->getCell().getY());
			d2->setCell(c);
		}else{
			c=Cell(d->getCell().getX(), s->getCell().getY()-1);
			s2->setCell(c);
			c=Cell(s->getCell().getX(), d->getCell().getY()-1);
			d2->setCell(c);
		}	
	}
	


	*this=(Road(s, s2, d, d2));
}

Road::Road(Position* s1, Position* s2, Position* d1, Position* d2){
	
	//Check if both lanes are the same size

	
	Cell disp1 = d1->getCell()-s1->getCell();
	Cell disp2 = d2->getCell()-s2->getCell();
	
	if(disp1.greatest() != disp2.greatest()){
		throw std::logic_error("Not same length");
	}
	
	//Check if it is oneway
	oneWay=(disp1==disp2);
	
	//Check if the lanes are adjacent
	if(oneWay){
		if(!((s1->getCell().getX()==s2->getCell().getX())||(s1->getCell().getY()==s2->getCell().getY()))){
			throw std::logic_error("Not adjacent");
		}
		Cell disp3 = d1->getCell()-d2->getCell();
		Cell disp4 = s1->getCell()-s2->getCell();
	
		if((disp3.greatest() != 1) || (disp4.greatest() != 1)){
			throw std::logic_error("Not adjacent");
		}
	
	}else{
		if(!((s1->getCell().getX()==d2->getCell().getX())||(s1->getCell().getY()==d2->getCell().getY()))){
			throw std::logic_error("Not adjacent");
		}
		Cell disp3 = d1->getCell()-s2->getCell();
		Cell disp4 = d2->getCell()-s1->getCell();
	
		if((disp3.greatest() != 1) || (disp4.greatest() != 1)){
			throw std::logic_error("Not adjacent");
		}
	}
	

	//Check if all lanes are inside the map
	if(!(d1->inMap() && d2->inMap() && s1->inMap() && s2->inMap())){
		throw std::logic_error("Outside map");
	}
	
	source_1=s1;
	source_2=s2;
	destination_1=d1;
	destination_2=d2;
	weight = abs(disp1.greatest());//(abs(disp1.greatest())>abs(disp2.greatest())) ? abs(disp1.greatest()) : abs(disp2.greatest());
	

}

Road::~Road(){}
	
bool Road::isoneWay()const{
		
	return oneWay;
}

int Road::getXmin()const{

	std::vector<int> v;
	v.push_back(source_1->getCell().getX());
	v.push_back(source_2->getCell().getX());
	v.push_back(destination_1->getCell().getX());
	v.push_back(destination_2->getCell().getX());
	
	return *(std::min_element(v.begin(),v.end()));
}
	

int Road::getYmin()const{

	std::vector<int> v;
	v.push_back(source_1->getCell().getY());
	v.push_back(source_2->getCell().getY());
	v.push_back(destination_1->getCell().getY());
	v.push_back(destination_2->getCell().getY());
	
	return *(std::min_element(v.begin(),v.end()));
}
	
unsigned int Road::getWeight()const{

	return weight;
}

Position* Road::getSource1()const{

	return source_1;
}
	
Position* Road::getSource2()const{

	return source_2;
}
	
Position* Road::getDestination1()const{

	return destination_1;
}
	
Position* Road::getDestination2()const{

	return destination_2;
}


bool Road::operator==(const Road& other)const{
	
	return ((weight==other.getWeight()) &&
		 (((*source_1==*(other.getSource1())) && (*source_2==*(other.getSource2())))  ||
		 ((*source_1==*(other.getSource2())) && (*source_2==*(other.getSource1())))  ));
}

Road& Road::operator=(const Road& other){
	
	this->destination_1=other.getDestination1();
	this->destination_2=other.getDestination2();
	this->source_1=other.getSource1();
	this->source_2=other.getSource2();
	this->weight=other.getWeight();
	this->oneWay=other.isoneWay();
	
	return *this;
}

bool Road::isHorizontal()const{

	return source_1->getCell().getY()==destination_1->getCell().getY();

}

bool Road::contains(const Position position) const {
	int x = position.getCell().getX();
	int y = position.getCell().getY();
	int x_min, x_max, y_min, y_max;
	bool between_x = false;
	bool between_y = false;
	x_min = std::min(std::min(source_1->getCell().getX(), destination_1->getCell().getX()),
			std::min(source_2->getCell().getX(), destination_2->getCell().getX()));
	x_max = std::max(std::max(source_1->getCell().getX(), destination_1->getCell().getX()),
			std::max(source_2->getCell().getX(), destination_2->getCell().getX()));
	y_min = std::min(std::min(source_1->getCell().getY(), destination_1->getCell().getY()),
			std::min(source_2->getCell().getY(), destination_2->getCell().getY()));
	y_max = std::max(std::max(source_1->getCell().getY(), destination_1->getCell().getY()),
			std::max(source_2->getCell().getY(), destination_2->getCell().getY()));
	between_x = (x_min <= x) && (x <= x_max);
	between_y = (y_min <= y) && (y <= y_max);
	return between_x && between_y;
}
