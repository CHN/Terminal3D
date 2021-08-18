project(GoogleTest)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set(UNIT_TEST_SOURCE_DIR "${PROJECT_SOURCE_DIR}/unitTestsSrc/")
file(GLOB_RECURSE UNIT_TEST_SOURCES "${UNIT_TEST_SOURCE_DIR}/*.c*")

add_executable(${PROJECT_NAME} ${UNIT_TEST_SOURCES})

target_link_libraries(${PROJECT_NAME} Terminal3D_lib)
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

list(LENGTH UNIT_TEST_SOURCES UNIT_TEST_SOURCE_COUNT)

if(UNIT_TEST_SOURCE_COUNT GREATER 0)
  add_test(NAME Test1 COMMAND ${UNIT_TEST_SOURCES})
endif()