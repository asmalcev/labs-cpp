#pragma once
#include "String.hpp"

class StringD : public String {
public:
  StringD();
  StringD(char);
  StringD(char const *);
  StringD(StringD const &);
  StringD& operator=(StringD const&);
  friend StringD operator+(StringD& left, const StringD& right);
  bool isPositive();
};