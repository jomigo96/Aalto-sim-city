#include "Car.hpp"

Car::Car(std::string name, int speed, sf::Color color, Position position, std::list<Road>& roads, std::list<Intersection>& intersections)
: Vehicle(name, speed, color, position, roads, intersections) {}

Car::~Car() {
}

