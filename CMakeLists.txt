cmake_minimum_required(VERSION 3.0)
project(ed2_um_estudo_sobre_algoritmos_gulosos)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage") #codecov
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/.travis/cmake) # modulo para codecov


include(CodeCoverage)

find_package(GTest REQUIRED)

add_executable(ed2_um_estudo_sobre_algoritmos_gulosos main.cpp)

target_link_libraries(ed2_um_estudo_sobre_algoritmos_gulosos GTest::GTest GTest::Main)

setup_target_for_coverage(coverage  ed2_um_estudo_sobre_algoritmos_gulosos  coverage)