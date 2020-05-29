#include "String.hpp"
#include <cstring>

String::String()
  : m_length(0), m_size(8), m_str(new char[m_size]) {
  LOG1()
  if (m_str != nullptr) {
    for (size_t i = 0; i < m_size; i++) {
      m_str[i] = '\0';
    }
  }
}

String::String(char c)
  : m_length(1), m_size(8), m_str(new char[m_size]) {
  if (m_str != nullptr) {
    for (size_t i = 0; i < m_size; i++) {
      m_str[i] = '\0';
    }
  }
  m_str[0] = c;
  LOG1()
}

String::String(const char* str)
  : m_length(strlen(str) + 1), m_size(m_length), m_str(new char[m_size]) {
  if (m_str != nullptr) {
    strncpy(m_str, str, m_size);
  }
  LOG1()
}

String::~String() {
  LOG1()
  delete[] m_str;
}

size_t String::length() const {
  LOG1()
  return m_length;
}

std::ostream& operator<<(std::ostream& os, String const & str) {
  LOG1()
  os << str.m_str;
  return os;
}

String& String::operator=(String const & other) {
  LOG1()
  if (this != &other) {
    if (other.m_size != m_size) {
      delete[] m_str;
      m_size = other.m_size;
      m_str = new char[other.m_size];
    } 
    if (m_str != nullptr) {
      strncpy(m_str, other.m_str, m_size);
    }
  }
  return *this;
}

String::String(String const & other) {
  countOfCall++;
  LOG1()
  if (this != &other) {
    if (other.m_size != m_size) {
      delete[] m_str;
      m_size = other.m_size;
      m_str = new char[other.m_size];
    } 
    if (m_str != nullptr) {
      strncpy(m_str, other.m_str, m_size);
    }
  }
}

size_t String::getCountOfCallCopy() {
  LOG1()
  return countOfCall;
}

size_t String::countOfCall = 0;