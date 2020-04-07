#include <iostream>
#include <cmath>
#include "Logger.hpp"
#include "Triangle.hpp"

float Triangle::getBisector(float a, float b, float c) {
	float sum = a + b;
	return sqrt(a*b*(sum + c)*(sum - c)) / sum;
}

Triangle::Triangle(float lengthOfSide, float firstAngle, float secondAngle, bool inDegrees) {
  side = lengthOfSide;
  angle2 = firstAngle;
  angle3 = secondAngle;
	degrees = inDegrees;

	#ifdef DEBUG_BUILD
		logger = new Logger("../logs/logs", "Triangle");
	#endif
	DEBUG("constructor", "object has been created");
}

Triangle::Triangle(const Triangle &other) {
	side = other.side;
	angle2 = other.angle2;
	angle3 = other.angle3;
	degrees = other.degrees;

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
	side = s;
	if (side == s) {
		DEBUG("setSide", "value of side has been changed");
		return true;
	} else {
		DEBUG("setSide", "couldn't change side value");
		return false;
	}
}

bool Triangle::setAngle1(float a) {
	angle2 = a;
	if (angle2 == a) {
		DEBUG("setAngle1", "value of angle1 has been changed");
		return true;
	} else {
		DEBUG("setAngle1", "couldn't change angle1 value");
		return false;
	}
}

bool Triangle::setAngle2(float a) {
	angle3 = a;
	if (angle3 == a) {
		DEBUG("setAngle2", "value of angle2 has been changed");
		return true;
	} else {
		DEBUG("setAngle2", "couldn't change angle2 value");
		return false;
	}
}

Triangle::lines Triangle::getSides() {
  lines sides;
  sides.line1 = side;
	float angle1 = degrees ? 180 - angle2 - angle3  : M_PI - angle2 - angle3;
	if (degrees) {
		sides.line2 = side / sin(angle1 * M_PI / 180) * sin(angle2 * M_PI / 180);
		sides.line3 = side / sin(angle1 * M_PI / 180) * sin(angle3 * M_PI / 180);
	} else {
		sides.line2 = side / sin(angle1) * sin(angle2);
		sides.line3 = side / sin(angle1) * sin(angle3);
	}

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
	if (degrees) {
		angle1 = M_PI - (angle2 + angle3) * M_PI / 180;
	} else {
		angle1 = M_PI - angle2 - angle3;
	}	
	float side2 = side / sin(angle1) * sin(angle2);

	DEBUG("getArea", "successfully returned area");

	return sin(angle3) * side * side2 / 2;
}

void Triangle::readUserInput() {
	std::cout << "Enter length of side: ";
	std::cin >> side;
	std::cout << "Enter first angle: ";
	std::cin >> angle2;
	std::cout << "Enter second angle: ";
	std::cin >> angle3;

	DEBUG("readUserInput", "successfully read user input");
}

void Triangle::printFields() {
	std::cout << "side: " << side << "; angle1: " << angle2 << " " << (degrees ? "degrees" : "radians") << "; angle2: " << angle3 << " " << (degrees ? "degrees" : "radians") << ";" << std::endl;
	DEBUG("printFields", "successfully printed fields of class");
}

bool Triangle::operator == (Triangle& left) {
	float s1 = left.getArea();
	float s2 = getArea();
	std::cout << s1 << " " << s2 << " ";
	return (fabs(s1 - s2) < __FLT_EPSILON__);
}

bool Triangle::toggleDegrees() {
	if (degrees) {
		degrees = false;
		angle2 *= (M_PI / 180);
		angle3 *= (M_PI / 180);
	} else {
		degrees = true;
		angle2 *= (180 / M_PI);
		angle3 *= (180 / M_PI);
	}

	DEBUG("toggleDegrees", "toggled degrees/radians mode");

	return degrees;
}

std::ostream& operator << (std::ostream &out, Triangle::lines& sides) {
	out << "side1: " << sides.line1 << "; side2: " << sides.line2 << "; side3: " << sides.line3 << ";";
	return out;
}