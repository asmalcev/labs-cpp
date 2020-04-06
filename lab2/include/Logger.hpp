#pragma once

class Logger {
  protected:
  std::string className;
  FILE* logStream;

  public:
  Logger(char* path, std::string name);
  ~Logger();
  void printLog(std::string method, std::string message);
};