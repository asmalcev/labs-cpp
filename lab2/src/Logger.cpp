#include <fstream>
#include "Logger.hpp"

Logger::Logger(char* path, char* name) {
  logStream = fopen(path, "w");
  className = name;
}

Logger::~Logger() {
  fclose(logStream);
}

void Logger::printLog(char* method, char* message) {
  fprintf(logStream, "%s::%s: %s\n", className, method, message);
}