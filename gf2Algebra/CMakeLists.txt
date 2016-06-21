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
  subsetIndexMap.hpp
  subsetIndexMap.cpp

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
  internal/dynamicElementImp.hpp
  internal/dynamicElementImp.cpp


  operations/addition.hpp
  operations/addition.hxx
  operations/additionAssignment.hpp
  operations/additionAssignment.hxx
  operations/multiplication.hpp
  operations/multiplication.hxx
  operations/copy.hpp
  #operations/copy.hxx




  io.hpp


  dynamicElement.hpp
  dynamicElement.cpp

  )

add_library(gf2Algebra ${SOURCES})

