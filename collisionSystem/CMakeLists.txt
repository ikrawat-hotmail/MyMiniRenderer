# collisionSystem library CMake configuration
# Note: This is a subdirectory project, output directories are set by parent CMakeLists.txt

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Header files (now in shared src/include directory)
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/collisionManager.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/rect.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/vector2f.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/vector3f.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/polygon2D.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../include/circle.h
)

# Source files for the library
set(LIB_SOURCES
    collision.cpp
)

# Test source files
set(TEST_SOURCES
    test/main.cpp
)

# Create shared library
add_library(collision SHARED ${LIB_SOURCES} ${HEADERS})

# Set library properties
set_target_properties(collision PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
    PUBLIC_HEADER "${HEADERS}"
)

# Include directories for the library (shared include directory)
target_include_directories(collision PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/src/external/glad/include
)

# Link with glad library
target_link_libraries(collision PUBLIC glad)

# Create executable for testing
add_executable(collision_test ${TEST_SOURCES})

# Link test executable with the library
target_link_libraries(collision_test PRIVATE collision)
target_include_directories(collision_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Installation rules (optional)
install(TARGETS collision collision_test
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    PUBLIC_HEADER DESTINATION include/collisionSystem
)
