set(
  SOURCES
  gf256.cpp
  gf256.hpp
  sparseElement.cpp
  sparseElement.hpp
  operations.hpp
  operations.cpp
  io.cpp
  io.hpp
)

add_library(gf2algebra ${SOURCES})

