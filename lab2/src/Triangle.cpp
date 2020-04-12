#include <iostream>
#include <cmath>
#include "Logger.hpp"
#include "Triangle.hpp"

float Triangle::getBisector(float a, float b, float c) {
	float sum = a + b;
	return sqrt(a*b*(sum + c)*(sum - c)) / sum;
}

Triangle::Triangle(float lengthOfSide, float firstAngle, float secondAngle) {
  side = lengthOfSide;
  angle2 = firstAngle;
  angle3 = secondAngle;

	if (angle2 + angle3 >= M_PI) {
		throw std::invalid_argument("Sum of 2 angles should be less than Pi");
	}
	if (side <= 0 || angle2 <= 0 || angle3 <= 0) {
		throw std::invalid_argument("Side and angles should be bellow 0");
	}

	#ifdef DEBUG_BUILD
		logger = new Logger("../logs/logs", "Triangle");
	#endif
	DEBUG("constructor", "object has been created");
}

Triangle::Triangle(const Triangle &other) {
	side = other.side;
	angle2 = other.angle2;
	angle3 = other.angle3;

	DEBUG("copyConstructor", "object has been copied");
	#ifdef DEBUG_BUILD
		delete logger;
	#endif
}

Triangle::~Triangle() {
	DEBUG("destructor", "object has been deleted");
}

float Triangle::getSide() const {
	DEBUG("getSide", "returned side");
	return side;
}

float Triangle::getAngle1() const {
	DEBUG("getAngle1", "returned angle2");
	return angle2;
}

float Triangle::getAngle2() const {
	DEBUG("getAngle2", "returned angle3");
	return angle3;
}

bool Triangle::setSide(float s) {
	if (s < 0) {
		DEBUG("setSide", "incorrect argument");
		return false;
	}
	side = s;
	DEBUG("setSide", "value of side has been changed");
	return true;
}

bool Triangle::setAngle1(float a) {
	if (a < 0 || a >= M_PI || a + angle3 >= M_PI) {
		DEBUG("setAngle1", "incorrect argument");
		return false;
	}
	angle2 = a;
	DEBUG("setAngle1", "value of angle1 has been changed");
	return true;
}

bool Triangle::setAngle2(float a) {
	if (a < 0 || a >= M_PI || a + angle2 >= M_PI) {
		DEBUG("setAngle2", "incorrect argument");
		return false;
	}
	angle3 = a;
	DEBUG("setAngle2", "value of angle2 has been changed");
	return true;
}

Triangle::lines Triangle::getSides() {
  lines sides;
  sides.line1 = side;
	float angle1 = M_PI - angle2 - angle3;
	sides.line2 = side / sin(angle1) * sin(angle2);
	sides.line3 = side / sin(angle1) * sin(angle3);

	DEBUG("getSides", "successfully returned sides");

	return sides;
}

Triangle::lines Triangle::getBisectors() {
	lines tmp, sides = getSides();
	tmp.line1 = getBisector(sides.line2, sides.line3, sides.line1);
	tmp.line2 = getBisector(sides.line1, sides.line3, sides.line2);
	tmp.line3 = getBisector(sides.line2, sides.line1, sides.line3);

	DEBUG("getBisectors", "successfully returned bisectors");

	return tmp;
}

float Triangle::getArea() {
	float angle1 = 0;
	angle1 = M_PI - angle2 - angle3;
	float side2 = side / sin(angle1) * sin(angle2);

	DEBUG("getArea", "successfully returned area");

	return sin(angle3) * side * side2 / 2;
}

void Triangle::readUserInput() {
	int control = 0;
	do {
		std::cout << "Enter length of side: ";
		std::cin >> side;
		control = std::cin.fail();
	} while(control);

	do {
		std::cout << "Enter first angle: ";
		std::cin >> angle2;
		if (std::cin.fail() || angle2 >= M_PI) {
			control = 1;
		}
	} while(control);
	
	do {
		std::cout << "Enter second angle: ";
		std::cin >> angle3;
		if (std::cin.fail() || angle2 >= M_PI || angle2 + angle3 >= M_PI) {
			control = 1;
		}
	} while (control);

	DEBUG("readUserInput", "successfully read user input");
}

bool Triangle::operator == (Triangle& left) {
	float s1 = left.getArea();
	float s2 = this->getArea();
	return (fabs(s1 - s2) <= __FLT_EPSILON__);
}

std::ostream& operator << (std::ostream &out, Triangle::lines& sides) {
	out << "side1: " << sides.line1 << "; side2: " << sides.line2 << "; side3: " << sides.line3 << ";";
	return out;
}