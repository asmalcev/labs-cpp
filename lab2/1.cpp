#include <iostream>
#include <cmath>

class Triangle {
  private:
  float side, angle2, angle3;


  public:
  struct lines {
    float line1;
    float line2;
    float line3;
  };

  Triangle(float lengthOfSide, float firstAngle, float secondAngle) {
    side = lengthOfSide;
    angle2 = firstAngle;
    angle3 = secondAngle;
  }

  lines getSides() {
		/* using sin theorem */
    lines sides;
    sides.line1 = side;
		float angle1 = M_PI - angle2 - angle3;
		sides.line2 = side / angle1 * angle2;
		sides.line3 = side / angle1 * angle3;

		return sides;
  }

	lines getBisectors() {
		/* https://www-formula.ru/2011-10-09-11-08-41 */
		lines tmp;

		return tmp;
  }

	float getArea() {
		float angle1 = M_PI - angle2 - angle3;
		float side2 = side / angle1 * angle2;

		return sin(angle3) * side * side2 / 2;
	}

};

bool operator == (Triangle& left, Triangle& right) {
	float s1 = left.getArea();
	float s2 = right.getArea();

	return abs(s1 - s2) < __FLT_EPSILON__;
}

std::ostream& operator << (std::ostream &out, Triangle::lines &sides) {
	out << "side1: " << sides.line1 << "; side2: " << sides.line2 << "; side3: " << sides.line3 << ";";
	return out;
}

int main() {

}