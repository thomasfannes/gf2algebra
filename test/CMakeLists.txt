set (Boost_USE_MULTITHREADED OFF)
find_package(Boost 1.53 COMPONENTS unit_test_framework REQUIRED)

include_directories(${PROJECT_SOURCE_DIR})

add_library(util util.hpp util.cpp)

add_executable(basicsTest basicsTest.cpp)
target_link_libraries(basicsTest util gf2Algebra ${Boost_LIBRARIES})
add_test(NAME basicsTest COMMAND basicsTest)

add_executable(dynamicElementImplTest dynamicElementImplTest.cpp)
target_link_libraries(dynamicElementImplTest util gf2Algebra ${Boost_LIBRARIES})
add_test(NAME dynamicElementImplTest COMMAND dynamicElementImplTest)


add_executable(dynamicAdditionTest dynamicAdditionTest.cpp)
target_link_libraries(dynamicAdditionTest util gf2Algebra ${Boost_LIBRARIES})
add_test(NAME dynamicAdditionTest COMMAND dynamicAdditionTest)

add_executable(dynamicMultiplicationTest dynamicMultiplicationTest.cpp)
target_link_libraries(dynamicMultiplicationTest util gf2Algebra ${Boost_LIBRARIES})
add_test(NAME dynamicMultiplicationTest COMMAND dynamicMultiplicationTest)


add_executable(multiplicationSpeedTest multiplicationSpeedTest.cpp)
target_link_libraries(multiplicationSpeedTest gf2Algebra ${Boost_LIBRARIES})
add_test(NAME multiplicationSpeedTest COMMAND multiplicationSpeedTest 3 100)

add_executable(facadeMultiplicationSpeedTest facadeMultiplicationSpeedTest.cpp)
target_link_libraries(facadeMultiplicationSpeedTest gf2Algebra ${Boost_LIBRARIES})
add_test(NAME facadeMultiplicationSpeedTest COMMAND facadeMultiplicationSpeedTest 3 100)



