set (Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.53 COMPONENTS unit_test_framework REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

add_library(util util.hpp util.cpp)
target_link_libraries(util gf2Algebra ${Boost_LIBRARIES})

add_executable(transformTest transformTest.cpp)
target_link_libraries(transformTest gf2Algebra util ${Boost_LIBRARIES})
add_test(NAME transformTest COMMAND transformTest)


