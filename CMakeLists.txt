PROJECT( FunWithSDL_Part1 CXX C )
CMAKE_MINIMUM_REQUIRED( VERSION 2.8)
FIND_PACKAGE( SDL REQUIRED)

SET( CMAKE_VERBOSE_MAKEFILE off)
SET( CMAKE_BUILD_TYPE Debug)
SET( mainApp main.cpp )
# Linux !
SET( SDL_includes /usr/local/include/SDL)

#SET( SDL_linkers /usr/local/lib/libSDL.so)
#SET( SDL_libs libSDL.so)

INCLUDE( "${PROJECT_SOURCE_DIR}")
INCLUDE_DIRECTORIES( "${SDL_includes}")

#LINK_DIRECTORIES( "§{SDL_linkers}")

LINK_LIBRARIES( ${SDL_LIBRARY})

ADD_EXECUTABLE( funPart1 ${mainApp})

#TARGET_LINK_LIBRARIES(funPart1 ${SDL_libs})
