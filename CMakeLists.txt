# jar cvfm cpp.jar src/MANIFEST.MF -C out/production/jnidemo/ JNICpp.class
# mkdir build && cd build
# cmake ..
# cmake --build .
# ./JniDemoCpp

cmake_minimum_required(VERSION 3.25)

find_package(Java REQUIRED)
find_package(JNI REQUIRED)

project(JniDemo VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories($ENV{JAVA_HOME}/include)
include_directories($ENV{JAVA_HOME}/include/darwin)
add_executable(JniDemoCpp src/main.cpp)
target_link_libraries(JniDemoCpp $ENV{JAVA_HOME}/lib/server/libjvm.dylib)