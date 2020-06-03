#include "StringD.hpp"
#include <regex>

StringD::StringD() : String() {
  LOG1()
}

StringD::StringD(char c) : String() {
  LOG1()
  if (c >= '0' && c <= '9') {
    m_str[0] = c;
    m_length = 1;
  }
}

StringD::StringD(char const * str) {
  LOG1()
  std::cmatch m;
  std::regex e ("[^(0-9)+-]");
  std::regex e2 ("[+-]");
  if (!(std::regex_search(str, m, e) || std::regex_search(str + 1, m, e2))) {
    delete[] m_str;
    m_size = m_length = strlen(str);
    m_str = new char[m_size];
    if (m_str != nullptr) {
      for (size_t i = 0; i < m_size + 1; i++) {
        m_str[i] = '\0';
      }
      strncpy(m_str, str, m_size);
    }
    m_str[m_length] = '\0';
  }
}

StringD& StringD::operator=(StringD const& other) {
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

StringD operator+(StringD& left, const StringD& right) {
  LOG1()
  int const result = atoi(left.m_str) + atoi(right.m_str);
  int i = 1;
  for (int r = result > 0 ? result : -result; r > 0; r /= 10, i++);
  char str[i + 1];
  sprintf(str, "%d", result);
  str[i] = '\0';
  return StringD(str);
}

bool StringD::isPositive() {
  return !(m_str[0] == '-');
}