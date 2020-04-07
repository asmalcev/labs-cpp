#include <fstream>
#include <cstring>
#include "Logger.hpp"

Logger::Logger(char* path, std::string name) {
  logStream = fopen(path, "a");
  className = name;
}

Logger::~Logger() {
  fclose(logStream);
}

void Logger::printLog(std::string method, std::string message) {
  fprintf(logStream, "%s::%s: %s\n", className.c_str(), method.c_str(), message.c_str());
}