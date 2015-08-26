CMAKE_MINIMUM_REQUIRED (VERSION 2.8)
PROJECT (url)

FILE (GLOB LIBURL_SOURCES src/*.c)
INCLUDE_DIRECTORIES (include/)
ADD_LIBRARY (url ${LIBURL_SOURCES})

OPTION (BUILD_TEST "Build run_test command" OFF)
IF (${BUILD_TEST})
  INCLUDE (ExternalProject)
  SET (VENDOR ${CMAKE_SOURCE_DIR}/vendor)

  # GoogleTest
  EXTERNALPROJECT_ADD (googletest
    GIT_REPOSITORY "${VENDOR}/gtest"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    INSTALL_COMMAND ""
    )

  EXTERNALPROJECT_GET_PROPERTY (googletest source_dir)
  INCLUDE_DIRECTORIES (${source_dir}/include)
  EXTERNALPROJECT_GET_PROPERTY (googletest binary_dir)
  LINK_DIRECTORIES (${binary_dir})

  FILE (GLOB TESTING_SOURCES test/*_test.cpp)
  ADD_EXECUTABLE (run_test ${TESTING_SOURCES})
  ADD_DEPENDENCIES (run_test googletest)
  TARGET_LINK_LIBRARIES (run_test
    gtest
    gtest_main
    pthread
    url
    )
ENDIF (${BUILD_TEST})
