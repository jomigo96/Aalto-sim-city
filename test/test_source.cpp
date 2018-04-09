#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "../src/Position.hpp"

TEST(test_position, test_equals) {
    Position p1;
    Position p2(1, 2);
    Position p3(sf::Vector2f(1, 2));
    
    p1.setX(1);
    p1.setY(2);
    
    EXPECT_EQ(p1.getX(), p2.getX());
    EXPECT_EQ(p2.getY(), p3.getY());
    EXPECT_EQ(p1, p3);
    
    p2.setX(5);
    
    EXPECT_NE(p1, p2);
}