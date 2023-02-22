# CMakeList.txt : CMake project for yield, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library(libYield
  "yield.c"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET libYield PROPERTY CXX_STANDARD 20)
endif()