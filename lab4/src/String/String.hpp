#pragma once
#include <iostream>

// #define DEBUG
#ifdef DEBUG
  #define LOG(...) printf(__VA_ARGS__)
#else
  #define LOG(...)
#endif

#define LOG1() LOG("File path: %s\nLine: %d\tFunc: %s\n", __FILE__, __LINE__, __FUNCTION__);

class String {
protected:
  size_t m_length;
  size_t m_size;
  char* m_str;
  static size_t countOfCall;

public:
  static size_t getCountOfCallCopy();
  String();
  String(char);
  String(char const *);
  String(String const &);
  String& operator=(String const&);
  ~String();
  size_t length() const;
  friend std::ostream& operator<<(std::ostream& os, const String& obj);

};