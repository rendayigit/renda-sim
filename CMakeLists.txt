cmake_minimum_required(VERSION 3.21)
project(renda-sim)

# Engine Library
add_subdirectory(Engine/src/)

# Models
add_subdirectory(Models/src/)

# Unit Tests

# add_subdirectory(Engine/tests/) # TODO(renda): Uncomment later
# add_subdirectory(Models/tests/) # TODO(renda): Uncomment later

add_dependencies(renda-sim-models renda-sim-engine)
