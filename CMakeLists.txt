# Minimum version requirement
cmake_minimum_required( VERSION 3.12 )

# Name of the project
project( CardsInfo )

# Find Qt modules
find_package( Qt6 REQUIRED COMPONENTS Core5Compat ) 

# Include build directory contents
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# List C++ source files
set( CPP_SOURCES CodeLibrary.cpp )

# Automatically handle MOC headers
set( CMAKE_AUTOMOC ON )

# Automatically handle UI files
set( CMAKE_AUTOUIC ON )

# Automatically handle resource files
set( CMAKE_AUTORCC ON )

# Create executable
add_executable( CardsInfo ${CPP_SOURCES} )

# Link Qt libraries
target_link_libraries( CardsInfo PRIVATE Qt6::Core5Compat )

