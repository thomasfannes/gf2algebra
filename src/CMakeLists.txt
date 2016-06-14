set(
  SOURCES
  gf256.cpp
  gf256.hpp
  z2k.hpp
  z2k.cpp
  sparseElement.cpp
  sparseElement.hpp
  denseElement.hpp
  denseElement.cpp
  operations.hpp
  operations.cpp
  io.cpp
  io.hpp
)

add_library(gf2algebra ${SOURCES})

