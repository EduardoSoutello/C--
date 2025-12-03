cmake_minimum_required(VERSION 3.9.0)
project(exemplo VERSION 0.1.0)

include(CTest)
enable_testing()
find_package(OpenCV REQUIRED)
find_package(OpenMP REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(exemplo trab2bim.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} OpenMP::OpenMP_CXX)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
