# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("yield_experiment")

# Add source to this project's executable.
add_executable (yield_experiment
  "main.c"
)

# Include sub-projects.
add_subdirectory ("yield")

target_link_libraries(yield_experiment
  libYield
)

target_include_directories(yield_experiment PRIVATE
  "yield"
)