#pragma once

class Logger {
  protected:
  char* className;
  FILE* logStream;

  public:
  Logger(char* path, char* name);
  ~Logger();
  void printLog(char* method, char* message);
};