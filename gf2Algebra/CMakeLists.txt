set(
  SOURCES
  gf2Algebra.hpp
  config.hpp
  config.cpp
  gf256.cpp
  gf256.hpp
  z2k.hpp
  z2k.cpp
  dynamicElement.hpp
  dynamicElement.cpp


  ext/representation.hpp
  ext/representation.hxx
  ext/representation.cpp

  ext/element.hpp
  ext/element.cpp
  ext/algebra.hpp
  ext/algebra.cpp

  ext/densePolynomial.hpp
  ext/densePolynomial.hxx
  ext/densePolynomialIO.hpp

  ext/fwht.hpp
  ext/fwht.cpp
  ext/fwht.hxx

  ext/iterator.hpp

  ext/internal/sparseRepresentationIterator.hpp
  ext/internal/sparseRepresentationIterator.hxx
  ext/internal/denseRepresentationIterator.hpp
  ext/internal/denseRepresentationIterator.hxx
  ext/internal/temporaryPointerProxy.hpp
  ext/internal/dynamicVisitors.hpp
  ext/internal/z2kMaskFunctor.hpp
  ext/internal/valueCoefficientPair.hpp
  ext/internal/valueCoefficientPair.hxx


  ext/identityIndexMap.hpp
  ext/subsetIndexMap.hpp
  ext/subsetIndexMap.cpp
  ext/addition.hpp
  ext/addition.hxx
  ext/additionAssignment.hpp
  ext/additionAssignment.hxx
  ext/multiplication.hpp
  ext/multiplication.hxx
  ext/copy.hpp
  ext/copy.hxx
  ext/streamify.hpp
  ext/streamify.hxx







  )

add_library(gf2Algebra ${SOURCES})

