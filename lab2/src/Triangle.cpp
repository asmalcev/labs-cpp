#include <iostream>
#include <cmath>
#include "Logger.hpp"
#include "Triangle.hpp"

float Triangle::getBisector(float a, float b, float c) {
	float sum = a + b;
	return sqrt(a*b*(sum + c)*(sum - c)) / sum;
}

Triangle::Triangle() {
  side = 0;
  angle2 = 0;
  angle3 = 0;

	#ifdef DEBUG
		logger = new Logger("../logs/logs", "Triangle");
		logger->printLog("constructor", "object has been created with no-args");
	#endif
}

Triangle::Triangle(float lengthOfSide, float firstAngle, float secondAngle) {
  side = lengthOfSide;
  angle2 = firstAngle;
  angle3 = secondAngle;

	#ifdef DEBUG
		logger = new Logger("../logs/logs", "Triangle");
		logger->printLog("constructor", "object has been created");
	#endif
}

Triangle::Triangle(const Triangle &other) {
	side = other.side;
	angle2 = other.angle2;
	angle3 = other.angle3;

	#ifdef DEBUG
		logger->printLog("copyConstructor", "object has been copied");
		delete logger;
	#endif
}

Triangle::~Triangle() {
	#ifdef DEBUG
		logger->printLog("destructor", "object has been deleted");
	#endif
}

float Triangle::getSide() const {
	#ifdef DEBUG
		logger->printLog("getSide", "returned side");
	#endif
	return side;
}

float Triangle::getAngle1() const {
	#ifdef DEBUG
		logger->printLog("getAngle1", "returned angle2");
	#endif
	return angle2;
}

float Triangle::getAngle2() const {
	#ifdef DEBUG
		logger->printLog("getAngle2", "returned angle3");
	#endif
	return angle3;
}

bool Triangle::setSide(float s) {
	side = s;
	if (side == s) {
		#ifdef DEBUG
			logger->printLog("setSide", "value of side has been changed");
		#endif
		return true;
	} else {
		#ifdef DEBUG
			logger->printLog("setSide", "couldn't change side value");
		#endif
		return false;
	}
}

bool Triangle::setAngle1(float a) {
	angle2 = a;
	if (angle2 == a) {
		#ifdef DEBUG
			logger->printLog("setAngle1", "value of angle1 has been changed");
		#endif
		return true;
	} else {
		#ifdef DEBUG
			logger->printLog("setAngle1", "couldn't change angle1 value");
		#endif
		return false;
	}
}

bool Triangle::setAngle2(float a) {
	angle3 = a;
	if (angle3 == a) {
		#ifdef DEBUG
			logger->printLog("setAngle2", "value of angle2 has been changed");
		#endif
		return true;
	} else {
		#ifdef DEBUG
			logger->printLog("setAngle2", "couldn't change angle2 value");
		#endif
		return false;
	}
}

Triangle::lines Triangle::getSides() {
  lines sides;
  sides.line1 = side;
	float angle1 = M_PI - angle2 - angle3;
	sides.line2 = side / angle1 * angle2;
	sides.line3 = side / angle1 * angle3;

	#ifdef DEBUG
		logger->printLog("getSides", "successfully returned sides");
	#endif

	return sides;
}

Triangle::lines Triangle::getBisectors() {
	lines tmp, sides = getSides();
	tmp.line1 = getBisector(sides.line2, sides.line3, sides.line1);
	tmp.line2 = getBisector(sides.line1, sides.line3, sides.line2);
	tmp.line3 = getBisector(sides.line2, sides.line1, sides.line3);

	#ifdef DEBUG
		logger->printLog("getBisectors", "successfully returned bisectors");
	#endif

	return tmp;
}

float Triangle::getArea() {
	float angle1 = M_PI - angle2 - angle3;
	float side2 = side / angle1 * angle2;

	#ifdef DEBUG
		logger->printLog("getArea", "successfully returned area");
	#endif

	return sin(angle3) * side * side2 / 2;
}

void Triangle::readUserInput() {
	std::cout << "Enter length of side: ";
	std::cin >> side;
	std::cout << "Enter first angle: ";
	std::cin >> angle2;
	std::cout << "Enter second angle: ";
	std::cin >> angle3;

	#ifdef DEBUG
		logger->printLog("readUserInput", "successfully read user input");
	#endif
}

void Triangle::printFields() {
	std::cout << "side: " << side << "; angle1: " << angle2 << " radians; angle2: " << angle3 << " radians;" << std::endl;
	#ifdef DEBUG
		logger->printLog("printFields", "successfully printed fields of class");
	#endif
}

bool Triangle::operator == (Triangle& left) {
	float s1 = left.getArea();
	float s2 = getArea();

	return abs(s1 - s2) < __FLT_EPSILON__;
}

std::ostream& operator << (std::ostream &out, Triangle::lines& sides) {
	out << "side1: " << sides.line1 << "; side2: " << sides.line2 << "; side3: " << sides.line3 << ";";
	return out;
}