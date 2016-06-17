set(
  SOURCES
  config.hpp
  config.cpp
  gf256.cpp
  gf256.hpp
  z2k.hpp
  z2k.cpp

  valueCoefficientPair.hpp
  valueCoefficientPair.cpp
  representation.hpp
  representation.cpp

  identityIndexMap.hpp

  iterator.hpp

  internal/sparseRepresentationIterator.hpp
  internal/sparseRepresentationIterator.cpp
  internal/denseRepresentationIterator.hpp
  internal/denseRepresentationIterator.hxx
  internal/storedCoefficientProxy.hpp
  internal/storedCoefficientProxy.cpp
  internal/temporaryPointerProxy.hpp
  internal/densePolynomial.hpp
  internal/densePolynomial.hxx
  internal/densePolynomialIO.hpp
  internal/fwht.hpp
  internal/fwht.cpp
  internal/fwht.hxx


  operations/addition.hpp
  operations/addition.hxx
  operations/additionAssignment.hpp
  operations/additionAssignment.hxx
  operations/multiply.hpp
  operations/multiply.hxx




  io.hpp


  )

add_library(gf2Algebra ${SOURCES})

