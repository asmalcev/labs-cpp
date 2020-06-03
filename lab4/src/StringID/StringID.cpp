#include "StringID.hpp"
#include <regex>

StringID::StringID() : String() {
  LOG1()
}

StringID::StringID(char c) : String() {
  LOG1()
  if ((c >= '0' && c <= '9')
   || (c >= 'a' && c <= 'z')
   || (c >= 'A' && c <= 'Z')
   || c == '_') {
    m_str[0] = c;
    m_length = 1;
  }
}

StringID::StringID(char const * str) {
  LOG1()
  std::cmatch m;
  std::regex e ("[^(a-z)(A-Z)(0-9)_]");
  if (!std::regex_search(str, m, e)) {
    delete[] m_str;
    m_size = m_length = strlen(str);
    m_str = new char[m_size + 1];
    if (m_str != nullptr) {
      for (size_t i = 0; i < m_size + 1; i++) {
        m_str[i] = '\0';
      }
      strncpy(m_str, str, m_size);
    }
  }
}

StringID& StringID::operator=(StringID const& other) {
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

StringID operator+(StringID& left, const StringID& right) {
  LOG1()
  char str[left.m_length + right.m_length];
  if (str != nullptr) {
    strncpy(str, left.m_str, left.m_length);
    strncpy(str + left.m_length, right.m_str, right.m_length);
  }
  str[left.m_length + right.m_length] = '\0';
  return StringID(str);
}

void StringID::upcase() {
  constexpr int diff = 'A' - 'a';
  for (size_t i = 0; i < m_length; i++) {
    if (m_str[i] >= 'a' && m_str[i] <= 'z') {
      m_str[i] += diff;
    }
  }
}