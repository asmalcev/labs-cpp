cmake_minimum_required(VERSION 3.5)

project(LAB4)

file(GLOB CPP_SOURCES
  "src/*.cpp",
  "src/String/*.cpp",
  "src/StringD/*.cpp",
  "src/StringID/*.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/src")
include_directories("${PROJECT_SOURCE_DIR}/src/String")
include_directories("${PROJECT_SOURCE_DIR}/src/StringD")
include_directories("${PROJECT_SOURCE_DIR}/src/StringID")

add_executable(${PROJECT_NAME} ${CPP_SOURCES})