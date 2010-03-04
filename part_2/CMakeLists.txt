PROJECT( FunWithSDL_Part1 CXX C )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8)
FIND_PACKAGE( SDL REQUIRED)

SET( cWindow cWindow.cpp cWindow.h)
SET( cEvent cEvent.cpp cEvent.h)
SET( cVariable cVariable.cpp cVariable.h)
SET( cDebugConsole cDebugConsole.cpp cDebugConsole.h)
SET( mainApp main.cpp main.h ${cVariable} ${cWindow} ${cEvent} ${cDebugConsole})


# Linux !

SET( CMAKE_VERBOSE_MAKEFILE on)

SET( CMAKE_CXX_COMPILER "g++")
SET( CMAKE_BUILD_TYPE Debug)
#SET( CMAKE_CXX_FLAGS "-Wall")
SET( CMAKE_CXX_FLAGS_DEBUG "-g -Wall -fprofile-arcs -ftest-coverage -pg")

SET( SDL_includes /usr/local/include/SDL)

INCLUDE( "${PROJECT_SOURCE_DIR}")
INCLUDE_DIRECTORIES( "${SDL_includes}")

LINK_LIBRARIES( ${SDL_LIBRARY})

ADD_EXECUTABLE( funPart2 ${mainApp})

