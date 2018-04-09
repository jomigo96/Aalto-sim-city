#include "MapEditor.hpp"

MapEditor::MapEditor(sf::RenderTexture& texture, Map& map, sf::Font font) : m_texture(texture), m_map(map), m_font(font) {
	m_texture.clear(sf::Color::White);
	speed_factor=1;
	traffic_intensity=1;
	init();
}

MapEditor::~MapEditor() {
}

void MapEditor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	m_texture.clear(sf::Color::White);
	
	// draw texts
	m_texture.draw(m_instructions_text);
	m_texture.draw(m_status_text);
	
	int x_speed = 20;
	int x_traffic = 100;
	int y = 650;
	int offsetY = 50;
	
	sf::Text speed_text;
	speed_text.setFont(m_font);
	speed_text.setString("Speed");
	speed_text.setCharacterSize(18);
	speed_text.setColor(sf::Color::Black);
	speed_text.setPosition(sf::Vector2f(x_speed, y));
	m_texture.draw(speed_text);
	
	sf::Text traffic_text;
	traffic_text.setFont(m_font);
	traffic_text.setString("Traffic");
	traffic_text.setCharacterSize(18);
	traffic_text.setColor(sf::Color::Black);
	traffic_text.setPosition(sf::Vector2f(x_traffic, y));
	m_texture.draw(traffic_text);
	
	// draw bars
	sf::RectangleShape speed_rec(sf::Vector2f(50, 150.0*speed_factor));
	speed_rec.setFillColor(sf::Color::Red);
	speed_rec.setPosition(x_speed, y + offsetY);
	m_texture.draw(speed_rec);
	
	sf::RectangleShape traffic_rec(sf::Vector2f(50, 150.0*traffic_intensity/1.75));
	traffic_rec.setFillColor(sf::Color::Green);
	traffic_rec.setPosition(x_traffic, y + offsetY);
	m_texture.draw(traffic_rec);
	
	m_texture.setSmooth(true);
	m_texture.display();
	sf::Sprite sprite(m_texture.getTexture());
	target.draw(sprite, states);
}

void MapEditor::init() {
	const char* instructions = "Instructions:\n"
	/*"i: Intersection\n"
	"r: Road\n"*/
	"p: Parking\n"
	"b: Building\n"
	"page up/down:\n\t+/- speed\n"
	"q/a: +/- traffic";
	m_instructions_text.setFont(m_font);
	m_instructions_text.setString(instructions);
	m_instructions_text.setCharacterSize(24);
	m_instructions_text.setColor(sf::Color::Black);
	m_instructions_text.setPosition(sf::Vector2f(20,0));
	
	m_status_text.setFont(m_font);
	m_status_text.setString("Waiting...");
	m_status_text.setCharacterSize(20);
	m_status_text.setColor(sf::Color::Black);
	m_status_text.setPosition(sf::Vector2f(0,0));
	m_status_text.setPosition(20,500);
}

void MapEditor::setStatus(int status) {
	m_status = status;
	switch (m_status) {
		case MapEditor::INTERSECTION:
			m_status_text.setString("Key pressed:\nIntersection\nSelect a cell");
			break;
		case MapEditor::ROAD_SOURCE_1:
			m_status_text.setString("Key pressed:\nRoad source 1\nSelect a cell");
			break;
		case MapEditor::ROAD_DESTINATION_1:
			m_status_text.setString("Road destination 1\nSelect a cell");
			break;
		case MapEditor::ROAD_SOURCE_2:
			m_status_text.setString("Road source 2\nSelect a cell");
			break;
		case MapEditor::ROAD_DESTINATION_2:
			m_status_text.setString("Road destination 2\nSelect a cell");
			break;
		case MapEditor::PARKING:
			m_status_text.setString("Key pressed:\nParking\nSelect a cell");
			break;
		case MapEditor::BUILDING:
			m_status_text.setString("Key pressed:\nBuilding\nSelect a cell");
			break;
		default:
			m_status_text.setString("Waiting...");
			break;
	}
	m_texture.draw(m_status_text);
}

int MapEditor::getStatus() const {
	return m_status;
}

void MapEditor::create(Position* position) {
	Parking* parking = nullptr;
	Building building(*position, m_map.getRoutes());
	switch (m_status) {
		case MapEditor::INTERSECTION:
			m_map.addIntersection(Intersection(*position, m_map.getRoutes()));
			setStatus(MapEditor::WAITING);
			break;
		case MapEditor::ROAD_SOURCE_1:
			m_src1 = position;
			setStatus(MapEditor::ROAD_DESTINATION_1);
			break;
		case MapEditor::ROAD_DESTINATION_1:
			m_dst1 = position;
			setStatus(MapEditor::ROAD_SOURCE_2);
			break;
		case MapEditor::ROAD_SOURCE_2:
			m_src2 = position;
			setStatus(MapEditor::ROAD_DESTINATION_2);
			break;
		case MapEditor::ROAD_DESTINATION_2:
			m_dst2 = position;
			try {
				m_map.addRoute(Road(m_src1, m_src2, m_dst1, m_dst2));
			} catch (std::exception e) {
				std::cout << e.what() << std::endl;
			}
			setStatus(MapEditor::WAITING);
			break;
		case MapEditor::PARKING:
			parking = new Parking(*position, m_map.getRoutes(), m_map.getIntersections(), m_map.getElapsedTime());
			m_map.addParking(parking);
			setStatus(MapEditor::WAITING);
			break;
		case MapEditor::BUILDING:
			m_map.addBuilding(building);
			setStatus(MapEditor::WAITING);
			break;
		default:
			break;
	}
}

void MapEditor::deleteItem(Position* position) {
	/*for (auto intersection : m_map.getIntersections()) {
		if (intersection.contains(*position)) {
			m_map.removeIntersection(intersection);
			return;
		}
	}
	
	for (auto road : m_map.getRoutes()) {
		if (road.contains(*position)) {
			m_map.removeRoute(road);
			return;
		}
	}*/
	
	for (auto parking : m_map.getParkings()) {
		if (parking->getPos() == *position) {
			m_map.removeParking(parking);
			return;
		}
	}
	
	for (auto building : m_map.getBuildings()) {
		if (building.getPos() == *position) {
			m_map.removeBuilding(building);
			return;
		}
	}
}

void MapEditor::setFactors(float speed, float intensity){
	speed_factor=speed;
	traffic_intensity=intensity;
}
