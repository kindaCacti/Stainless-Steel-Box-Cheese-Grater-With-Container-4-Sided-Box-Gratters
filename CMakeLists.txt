cmake_minimum_required(VERSION 3.11.0)
project(stack VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare( 
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(API_FOLDER CheesyApi)
set(API_SOURCES
   ${API_FOLDER}/piece.h
   ${API_FOLDER}/pieces.h
   ${API_FOLDER}/cheeseApi.h
   ${API_FOLDER}/cheeseApi.cpp
)
set(BOT_SOURCES)
set(PROJECT_SOURCES ${API_SOURCES} ${BOT_SOURCES})

add_executable(entry main.cpp ${PROJECT_SOURCES} )

# add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
