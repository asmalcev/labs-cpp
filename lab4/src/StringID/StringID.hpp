#pragma once
#include "String.hpp"

class StringID : public String {
public:
  StringID();
  StringID(char);
  StringID(char const *);
  StringID(StringID const &);
  StringID& operator=(StringID const&);
  friend StringID operator+(StringID& left, const StringID& right);
  void upcase();
  
};

