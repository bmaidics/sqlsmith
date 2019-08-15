# Install script for directory: /Users/barnabasmaidics/hs2client/src/hs2client

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RELEASE")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/hs2client" TYPE FILE FILES
    "/Users/barnabasmaidics/hs2client/src/hs2client/api.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/columnar-row-set.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/logging.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/macros.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/operation.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/service.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/session.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/status.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/types.h"
    "/Users/barnabasmaidics/hs2client/src/hs2client/util.h"
    )
endif()

