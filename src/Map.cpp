#include "Map.hpp"
#include <iostream>
Map::Map(sf::RenderTexture& texture) : m_texture(texture) {
    this->clear();
    this->drawGrid();
}

Map::~Map() {
	

}

void Map::drawGrid() {
    for (unsigned int i = 0 ; i < N; i++) {
        sf::Vertex verticalLine[] =
        {
            // source
            sf::Vertex(sf::Vector2f(i*CELL_DIM, 0), sf::Color::Black),
            // destination
            sf::Vertex(sf::Vector2f(i*CELL_DIM, MAP_DIM), sf::Color::Black)
        };
        sf::Vertex horizontalLine[] =
        {
            // source
            sf::Vertex(sf::Vector2f(0, i*CELL_DIM), sf::Color::Black),
            // destination
            sf::Vertex(sf::Vector2f(MAP_DIM, i*CELL_DIM), sf::Color::Black)
        };
        m_texture.draw(verticalLine, 2, sf::Lines);
        m_texture.draw(horizontalLine, 2, sf::Lines);
    }
}

void Map::clear() {
    m_texture.clear(sf::Color::White);
}

sf::Sprite Map::getSprite() const {
    sf::Sprite sprite(m_texture.getTexture());
    return sprite;
}

void Map::addVehicle(Vehicle* vehicle) {
    m_vehicles.push_back(vehicle);
}

void Map::draw(sf::RenderWindow& window) const {
    window.draw(getSprite());
    
    sf::Sprite road_sprite(road_texture);
	
	road_sprite.setScale((float)CELL_DIM/118, (float)CELL_DIM/118);

	
	int xmin, ymin;
	
    //For all roads, adjust position, rotation and print
    for(auto i : m_routes){
		

		xmin=i.getXmin();
		ymin=i.getYmin();

		
		if(i.isHorizontal()){
			
			road_sprite.setRotation(90);
			
			for(unsigned int j=i.getWeight(); j>0; j--){

				road_sprite.setPosition((xmin+j+1)*CELL_DIM, ymin*CELL_DIM);	
				window.draw(road_sprite);
			}
			
		}
		else{
			road_sprite.setRotation(0);
			
			for(unsigned int j=0; j<i.getWeight(); j++){
				road_sprite.setPosition(xmin*CELL_DIM, (ymin+j)*CELL_DIM);	
				window.draw(road_sprite);
	
			}
			
		}	
	}
    
    sf::Sprite intersection_sprite(int_texture);
	intersection_sprite.setScale(2*(float)CELL_DIM/280, 2*(float)CELL_DIM/280);
	intersection_sprite.setColor(road_sprite.getColor());


	sf::CircleShape light((float)CELL_DIM*0.1, 30);
	light.setOrigin((float)CELL_DIM*0.1, (float)CELL_DIM*0.1);
	
	//Print for all intersections
	for (auto i : m_intersections){
		
		sf::Vector2f ipos = i.getPos().getPos();
		
		intersection_sprite.setPosition(ipos);
		window.draw(intersection_sprite);
		
		light.setFillColor((i.getWay()==top) ? sf::Color::Green : sf::Color::Red);
		light.setPosition(ipos+sf::Vector2f(CELL_DIM, 0.1*(float)CELL_DIM));
		window.draw(light);
		
		light.setFillColor((i.getWay()==left) ? sf::Color::Green : sf::Color::Red);
		light.setPosition(ipos+sf::Vector2f(1.9*(float)CELL_DIM, CELL_DIM));
		window.draw(light);
		
		light.setFillColor((i.getWay()==down) ? sf::Color::Green : sf::Color::Red);
		light.setPosition(ipos+sf::Vector2f(CELL_DIM, 1.9*(float)CELL_DIM));
		window.draw(light);
		
		light.setFillColor((i.getWay()==right) ? sf::Color::Green : sf::Color::Red);
		light.setPosition(ipos+sf::Vector2f(0.1*(float)CELL_DIM, CELL_DIM));
		window.draw(light);
	}
    
    
    sf::Sprite car_sprite(car_texture);
    car_sprite.setScale((float)CELL_DIM*0.95/800, (float)CELL_DIM*0.70/397);
    car_sprite.setOrigin(0,(float)CELL_DIM/2);
    
	for(Vehicle* vehicle : m_vehicles){
		
		sf::Vector2f pos=vehicle->getPosition().getPos();
		
		switch (vehicle->getOrient()){
			
			case 0: 
				//car_sprite.setOrigin(0,(float)CELL_DIM*0.15);
				car_sprite.setPosition(pos.x, pos.y+(float)CELL_DIM*0.15);
				break;
			case 90: 
				//car_sprite.setOrigin((float)CELL_DIM*0.85,0);
				car_sprite.setPosition(pos.x+(float)CELL_DIM*0.85, pos.y);
				break;
			case 180: 
				//car_sprite.setOrigin((float)CELL_DIM,(float)CELL_DIM*0.85);
				car_sprite.setPosition(pos.x+CELL_DIM, pos.y+(float)CELL_DIM*0.85);
				break;
			case 270:
				//car_sprite.setOrigin((float)CELL_DIM*0.15, CELL_DIM);
				car_sprite.setPosition(pos.x+(float)CELL_DIM*.15, pos.y+CELL_DIM);
				break;
			default: break;
		}
		
		
		car_sprite.setRotation(vehicle->getOrient());
		window.draw(car_sprite);
		
	}

	for (Parking* parking : m_parkings) {
		window.draw(parking->getShape());
	}
	
	for (Building building : m_buildings) {
		window.draw(building.getShape());
	}
}

void Map::setRoadTexture(const sf::Texture& tex){
	
	road_texture=tex;
}



bool Map::addRoute(const Road& r){
	
	//Much more logic needed
	
	for(auto i : m_routes){
		
		if(i==r)
			return true; //Already exists
	}
	m_routes.push_back(r);
	return true;
}
    
    
std::list<Road>& Map::getRoutes(){
	
	return m_routes;
}
    
    
void Map::removeRoute(Road r){
	
	m_routes.remove(r);
}

void Map::removeIntersection(Intersection intersection) {
	m_intersections.remove(intersection);
}

void Map::setIntersectionTexture(const sf::Texture& tex){
	
	int_texture=tex;
}

void Map::setCarTexture(const sf::Texture& tex){

	car_texture=tex;
}

bool Map::addIntersection(const Intersection& i){
	
	//More logic required
	
	m_intersections.push_back(i);
	return true;
}

std::list<Intersection>& Map::getIntersections(){
	
	return m_intersections;
}

void Map::stepPositions(const float elapsed){
	
	std::vector<Vehicle*> finished_vehicles;
	
	for(Vehicle* vehicle : m_vehicles){
		
		
		bool conflict=false;
		
		Cell c1=vehicle->getNextNextPosition().getCell();
		Cell c2=vehicle->getNextPosition().getCell();
		Cell c3=vehicle->getPosition().getCell();
		for(Vehicle* others : m_vehicles){
			
			if(others==vehicle)
				continue;
				
			//check for conflicts
			Cell c4=others->getPosition().getCell();
			
			
			if(c2==c4){
				conflict=true;
				//break;
			}
			
			//Next node still corresponds to the current position
			//Need to check the next one
			if(c3==c2){
				if (c4==c1)
					conflict=true;
					//break;
			}
			
		}
		
		//Check if the vehicle is waiting on an Intersection
		if(this->atEndofRoad(vehicle->getPosition())){
			
			Intersection in = this->whichIntersection(vehicle->getPosition());
			
			//Check if there are other vehicles at the intersection
			/*for(Vehicle* others : m_vehicles){
			
				if(others==vehicle)
					continue;
				
				Cell c1 = others->getPosition().getCell();
				Cell c2 = in.getPos().getCell();
				
				if ((c1==c2) || (c1+Cell(1,0)==c2) || (c1+Cell(0,1)==c2) || (c1+Cell(1,1)==c2)){
					
					conflict=true;
					break;
				}
			
			}*/
		
			
			Cell disp = vehicle->getPosition().getCell() - in.getPos().getCell(); 
			
			
			if (disp==Cell(2,0)||disp==Cell(2,1))
				if(in.getWay()!=left)
					conflict=true;
			
			if (disp==Cell(0,-1)||disp==Cell(1,-1))
				if(in.getWay()!=top)
					conflict=true;
					
			if (disp==Cell(-1,0)||disp==Cell(-1,1))
				if(in.getWay()!=right)
					conflict=true;	
					
			if (disp==Cell(0,2)||disp==Cell(1,2))
				if(in.getWay()!=down)
					conflict=true;		
		}
		
		//If the vehicle is going left or up, it might still have room to move
		if(vehicle->getOrient()==180){
			
			int room = (int)vehicle->getPosition().getX() % CELL_DIM;
			
			if (room >= vehicle->getSpeed()*elapsed)
				conflict=false;
		}
		if(vehicle->getOrient()==270){
			
			int room = (int)vehicle->getPosition().getY() % CELL_DIM;
			
			if (room >= vehicle->getSpeed()*elapsed)
				conflict=false;
		}
		if(!conflict) 
			if(vehicle->updatePosition(elapsed))
				if (vehicle->getPath().isEmpty()) {
					finished_vehicles.push_back(vehicle);
				}
	}	
	
	// remove vehicles that have reached their destination
	
	for (auto v : finished_vehicles){
		
		for (auto it= m_vehicles.begin(); it!=m_vehicles.end(); it++){
			if (v==*it){
				m_vehicles.erase(it);
				break;
			}
		}
	}
}

void Map::toggleIntersections(){
	
	for(auto i = m_intersections.begin(); i!=m_intersections.end(); i++){
		i->toggle();
	}
}


bool Map::atEndofRoad(Position pos)const{
	
	for (auto r : m_routes){
		
		if((r.getDestination2()->getCell()==pos.getCell()) || (r.getDestination1()->getCell()==pos.getCell())) 
			return true;
	}
	return false;
}
	
Intersection Map::whichIntersection(Position pos)const{
	
	Cell c,c1,c2;
	
	
	for (auto r : m_routes){
		
		if(r.getDestination1()->getCell()==pos.getCell()){
			c1=r.getDestination1()->getCell();
			c2=r.getSource1()->getCell();
			break;
		}
		
		if(r.getDestination2()->getCell()==pos.getCell()){
			c1=r.getDestination2()->getCell();
			c2=r.getSource2()->getCell();
			break;
		}	
	}
	
	if(c1.getY()==c2.getY()){
		if(c1.getX()>c2.getX())
			c=c1+Cell(1,0);
		else
			c=c1-Cell(1,0);
	}else{
		if(c1.getY()>c2.getY())
			c=c1+Cell(0,1);
		else
			c=c1-Cell(0,1);
	}
	
	for (auto i : m_intersections){
		
		Cell c3=i.getPos().getCell();
		Cell c4=c3 + Cell(1,0);
		Cell c5=c3 + Cell(0,1);
		Cell c6=c3 + Cell(1,1);
		
		if((c==c3)||(c==c4)||(c==c5)||(c==c6))
			return i;
	}
	
	throw std::bad_function_call();
}


void Map::addParking(Parking* parking) {
	
	
	
	Cell c = parking->getPos().getCell();
	
	if(this->isOccupied(c))
		return;
	
	for (auto r : m_routes){
		
		int x = r.getXmin();
		int y = r.getYmin();
		
		if(r.isHorizontal()){
			if( ((c.getX()>x)&&(c.getX()<(x+(int)r.getWeight()))) && (((y-c.getY())==1)||((c.getY()-y)==2)) )
				m_parkings.push_back(parking);
		}
		else{
			if( ((c.getY()>y)&&(c.getY()<(y+(int)r.getWeight()))) && (((x-c.getX())==1)||((c.getX()-x)==2)) )
				m_parkings.push_back(parking);
		}
		
	}
	
	
	
}

void Map::removeParking(Parking* parking) {
	m_parkings.remove(parking);
}

void Map::generateTraffic() {
	for (Parking* parking : m_parkings) {
		Car* car = parking->createCar(m_elapsed, m_vehicles);
		if (car) {
			Position* destination = findDestination(car->getPosition());
			if (destination) {
				car->goTo(*destination);
				this->addVehicle(car);
			}
		}
	}
}

void Map::setElapsedTime(const int elapsed) {
	m_elapsed = elapsed;
}

int Map::getElapsedTime() const {
	return m_elapsed;
}

Position* Map::findDestination(Position source) const {
	std::vector<Position> destinations;
	Position dst;
	int index = 0;
	for (Building building : m_buildings) {
		if (building.hasAdjacentPositions() && *(building.getAdjacentsPositionsIt()) != source) {
			destinations.push_back(*building.getAdjacentsPositionsIt());
		}
	}
	for (Parking* parking : m_parkings) {
		if (parking->hasAdjacentPositions() && *(parking->getAdjacentsPositionsIt()) != source) {
			destinations.push_back(*(parking->getAdjacentsPositionsIt()));
		}
	}
	if (!destinations.empty()) {
		index = std::rand() % destinations.size();
		dst = destinations.at(index);
		return new Position(Cell(dst.getCell().getX(), dst.getCell().getY()));
	}
	return nullptr;
}

void Map::addBuilding(Building building) {
	
	Cell c = building.getPos().getCell();
	
	if(this->isOccupied(c))
		return;
	
	for (auto r : m_routes){
		
		int x = r.getXmin();
		int y = r.getYmin();
		
		if(r.isHorizontal()){
			if( ((c.getX()>x)&&(c.getX()<(x+(int)r.getWeight()))) && (((y-c.getY())==1)||((c.getY()-y)==2)) )
				m_buildings.push_back(building);
		}
		else{
			if( ((c.getY()>y)&&(c.getY()<(y+(int)r.getWeight()))) && (((x-c.getX())==1)||((c.getX()-x)==2)) )
				m_buildings.push_back(building);
		}
		
	}
	
	
	
	
}

void Map::removeBuilding(Building building) {
	m_buildings.remove(building);
}

void Map::changeSpeeds(const int speed){
	
	for(auto v : m_vehicles){
		
		v->setSpeed(speed);
	}
	
	
}

std::list<Parking*>& Map::getParkings() {
	return m_parkings;
}

std::list<Building>& Map::getBuildings() {
	return m_buildings;
}


bool Map::isOccupied(Cell c)const{
	
	Cell c2;
	
	for (auto i : m_intersections){
	
		c2= i.getPos().getCell();
		
		if( (c2==c) || ((c2+Cell(1,0))==c) || ((c2+Cell(0,1))==c) || ((c2+Cell(1,1))==c) )
			return true;
	}
	
	for (auto b : m_buildings){
		
		c2=b.getPos().getCell();
		if(c2==c)
			return true;
	}
	
	for (auto p : m_parkings){
	
		c2=p->getPos().getCell();
		if(c2==c)
			return true;
	}
	
	for (auto r : m_routes){
		
		int x = r.getXmin();
		int y = r.getYmin();
		int w = (int)r.getWeight();
		
		if(r.isHorizontal()){
			
			if((c.getX()>=x)&&(c.getX()<=(x+w))&&((c.getY()==y)||(c.getY()==(y+1))))
				return true;
		}
		else{
			
			if((c.getY()>=y)&&(c.getY()<=(y+w))&&((c.getX()==x)||(c.getX()==(x+1))))
				return true;
			
		}
	}
	return false;
}
