#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include "Map.hpp"
#include "Car.hpp"
#include "DijkstraPathSelector.hpp"
#include "MapEditor.hpp"

//Screen dimension constants
#define SCREEN_WIDTH MAP_DIM + MAP_EDITOR_WIDTH
#define SCREEN_HEIGHT MAP_DIM




int main(int argc, char* args[]) {
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Sim city 2");
    window.setFramerateLimit(60);
	
    sf::View view;
	view.setViewport(sf::FloatRect(0, 0, 0.8f, 1));
	
	sf::View editorView;
	editorView.setViewport(sf::FloatRect(0.8f, 0, 1, 1));
    
    sf::RenderTexture mapTexture;
    if (!mapTexture.create(MAP_DIM, MAP_DIM)) {
        std::cout << "Error while creating map texture!" << std::endl;
        return EXIT_FAILURE;
    }
	
	sf::RenderTexture editorTexture;
    if (!editorTexture.create(MAP_EDITOR_WIDTH, SCREEN_HEIGHT)) {
        std::cout << "Error while creating map editor texture!" << std::endl;
        return EXIT_FAILURE;
    }

    sf::Texture road_texture;
    sf::Texture intersection_texture;
    sf::Texture car_texture;


	if(!road_texture.loadFromFile("textures/Road.jpg")){
		
		std::cout << "Error while loading Road texture!" << std::endl;
        return EXIT_FAILURE;
	}
	
	if(!intersection_texture.loadFromFile("textures/Pavement.jpg")){
		
		std::cout << "Error while loading pavement texture!" << std::endl;
        return EXIT_FAILURE;
	}
	
	if(!car_texture.loadFromFile("textures/car1.png")){
		
		std::cout << "Error while loading car texture!" << std::endl;
		return EXIT_FAILURE;
		
	}
	
	sf::Font font;
	if (!font.loadFromFile("fonts/arial.ttf")) {
		std::cout << "Error while loading font!" << std::endl;
		return EXIT_FAILURE;
	}
	
	float speed_factor=1;
	float traffic_intensity=1;
	
    Map map(mapTexture);
    map.setRoadTexture(road_texture);
    map.setIntersectionTexture(intersection_texture);
    map.setCarTexture(car_texture);
    
	MapEditor editor(editorTexture, map, font);

	//Map loader
	std::ifstream inFile;
	inFile.open("files/map1.txt", std::ios::in);

	if(!inFile.is_open()){
		
		std::cout<<"Error opening map file!"<<std::endl;
		return EXIT_FAILURE;
	}
try{   
    char first,c;
    int x1,y1,x2,y2;
    
    inFile.get(first);

    while(first != 'S'){
			
		switch(first){
			case 'R':{
				
				inFile >> c >> x1 >> c >> y1 >> c >> x2 >> c >> y2;
				
				Position* p1= new Position(Cell(x1,y1));
				Position* p2= new Position(Cell(x2,y2));
				map.addRoute(Road(false, p1,p2));
				break;
			}
			case 'I':{
				inFile >> c >> x1 >> c >> y1;
				map.addIntersection(Intersection(Position(Cell(x1,y1)), map.getRoutes()));
				
				break;
			}
			case 'B':{
				
				inFile >> c >> x1 >> c >> y1;
				map.addBuilding(Building(Position(Cell(x1,y1)), map.getRoutes()));
				
				break;
			}
			case 'P':{
				
				inFile >> c >> x1 >> c >> y1;
				Parking* parking1 = new Parking(Position(Cell(x1,y1)), map.getRoutes(), map.getIntersections(), 0);
				map.addParking(parking1);
				
				break;
			}
			default: break;
		}
		while(inFile.get()!=10)
			;
		inFile.get(first);
	}
	inFile.close();
	
}catch(std::exception &e){
	
		std::cout<<"An error occurred: "<< e.what() <<std::endl;
		return EXIT_FAILURE;
}
	//End of Map loader
	
	
	
	sf::Clock globalClock; // For spawning
    sf::Clock clock; // For framerate
    sf::Clock clock2; // For traffic lights
    
    
    //Main loop
    while (window.isOpen())
    {
		// elapsed time in one loop
		sf::Time elapsed = clock.restart();
		
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                
                case sf::Event::MouseWheelMoved:
					if(event.mouseWheel.delta>0)
						view.zoom(0.9);
					else
						view.zoom(1.1);
					break;
					
				
     			case sf::Event::MouseButtonPressed:
				
					switch(event.key.code){
						
						case sf::Mouse::Left:
						{ 
							sf::Vector2f mouse_pos( window.mapPixelToCoords( sf::Mouse::getPosition(window), view ) );
							
							Position* p = new Position(mouse_pos); // position defined by pixel coordinates
							p->setCell(p->getCell()); // position defined by grid coordinates
							editor.create(p);
							break; 
						}
						
						case sf::Mouse::Right:
						{
							sf::Vector2f mouse_pos( window.mapPixelToCoords( sf::Mouse::getPosition(window), view ) );
							
							Position* p = new Position(mouse_pos); // position defined by pixel coordinates
							p->setCell(p->getCell()); // position defined by grid coordinates
							editor.deleteItem(p);
							break;
						}
						
						default:
							break;
						
					}
				
					break;

            
				case sf::Event::KeyPressed:
				
					switch(event.key.code){
						
						//View related keys
						case sf::Keyboard::Home:
							view.reset(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
							break;
						
							
						case sf::Keyboard::Up:
						
							view.move(0, -50);
							break;
						case sf::Keyboard::Down:
							
							view.move(0, 50);
							break;
						case sf::Keyboard::Left:
							
							view.move(-50, 0);
							break;
							
						case sf::Keyboard::Right:
						
							view.move(50, 0);
							break;
						
						// Keys related to the map editor
						/*case sf::Keyboard::I:
							editor.setStatus(MapEditor::INTERSECTION);
							break;
						case sf::Keyboard::R:
							editor.setStatus(MapEditor::ROAD_SOURCE_1);
							break;*/
						case sf::Keyboard::P:
							editor.setStatus(MapEditor::PARKING);
							break;
						case sf::Keyboard::B:
							editor.setStatus(MapEditor::BUILDING);
							break;
							
						// Keys related to speed adjustment
						
						case sf::Keyboard::PageUp:
							
							if(speed_factor<=1.5){
							
								speed_factor+=0.25;
							}
							break;
							
						case sf::Keyboard::PageDown:
							
							if(speed_factor>=0.75){
								speed_factor-=0.25;
							}
							break;
						
						case sf::Keyboard::Q:
						
							if(traffic_intensity<3){
							
								traffic_intensity+=0.25;
							}
							
							break;
							
						case sf::Keyboard::A:
						
							if(traffic_intensity>=0.5){
							
								traffic_intensity-=0.25;
							}
							
							break;
							
						//Other Keys
						default:
							break;
						
					}
					
					break;
                
                default:
                    break;
                    
                
                    
             }       
                
        }
        
        //Update the position of all vehicles
		map.stepPositions(elapsed.asSeconds());
		map.changeSpeeds(BASE_SPEED*speed_factor);
        
		map.setElapsedTime((int)globalClock.getElapsedTime().asSeconds()*traffic_intensity*speed_factor);
		map.generateTraffic();

        // We're done drawing to the texture
        mapTexture.display();
        
        // Now we start rendering to the window, clear it first
        window.clear();
        window.setView(view);
        
        //Draw all objects
        map.draw(window);
		
		window.setView(editorView);
		editor.setFactors(speed_factor, traffic_intensity);
		window.draw(editor);
  
        // End the current frame and display its contents on screen
        window.display();
        
        // switch traffic lights
        if(clock2.getElapsedTime().asSeconds()*speed_factor>=INTERSECTION_TIME){
			
			clock2.restart();
			map.toggleIntersections();
		}
    }

    return EXIT_SUCCESS;
}




