# rigidBody library CMake configuration
# Note: This is a subdirectory project, output directories are set by parent CMakeLists.txt

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Header files (now in shared src/include directory)
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/rigidBody2D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/vector2f.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/vector3f.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/polygon2D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/circle.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/sj.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/modelLoader.h
)

# Source files for the library
set(LIB_SOURCES
    rigidBody2D.cpp
    modelloader.cpp
)

# Create shared library
add_library(rigidBody SHARED ${LIB_SOURCES} ${HEADERS})

# Set library properties
set_target_properties(rigidBody PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}"
)

# Include directories for the library (shared include directory)
target_include_directories(rigidBody PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/src/external/glad/include
)

# Link with glad library
target_link_libraries(rigidBody PUBLIC glad)

# Test executable for rigidBody parser
add_executable(rigidBodyParserTest test/rigidbodyParserTest.cpp)

# Link test with rigidBody library
target_link_libraries(rigidBodyParserTest PRIVATE rigidBody)
target_include_directories(rigidBodyParserTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Test executable for model loader
add_executable(modelLoaderTest test/modelLoaderTest.cpp)

# Link test with rigidBody library
target_link_libraries(modelLoaderTest PRIVATE rigidBody)
target_include_directories(modelLoaderTest PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Test executable for model loader with colliders (sample2.json)
add_executable(modelLoaderTest2 test/modelLoaderTest2.cpp)

# Link test with rigidBody library
target_link_libraries(modelLoaderTest2 PRIVATE rigidBody)
target_include_directories(modelLoaderTest2 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Installation rules (optional)
install(TARGETS rigidBody rigidBodyParserTest modelLoaderTest modelLoaderTest2
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/rigidBody
)
