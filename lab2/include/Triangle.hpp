#pragma once
#include "Logger.hpp"

// #define DEBUG

class Triangle {
  protected:
  float side, angle2, angle3;
	float getBisector(float a, float b, float c);
	bool degrees;

	#ifdef DEBUG
  Logger* logger;
	#endif

  public:
  struct lines {
    float line1;
    float line2;
    float line3;
  };

  Triangle(float lengthOfSide, float firstAngle, float secondAngle, bool isDegrees);
	Triangle(const Triangle &other);
	~Triangle();
	float getSide() const;
	float getAngle1() const;
	float getAngle2() const;
	bool setSide(float s);
	bool setAngle1(float a);
	bool setAngle2(float a);
  lines getSides();
	lines getBisectors();
	float getArea();
	void readUserInput();
	void printFields();
	bool operator==(Triangle& left);
	bool toggleDegrees();

};