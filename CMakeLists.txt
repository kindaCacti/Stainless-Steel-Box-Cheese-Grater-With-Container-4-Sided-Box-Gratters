cmake_minimum_required(VERSION 3.11.0)
project(cheese VERSION 0.1.0)

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
set(BOT_FOLDER CheesyBot)
set(APP_FOLDER CheesyApp)
set(API_SOURCES
   ${API_FOLDER}/board.h
   # ${API_FOLDER}/board.h
   ${API_FOLDER}/game.h
   ${API_FOLDER}/pieces.cpp
)
set(BOT_SOURCES
   ${BOT_FOLDER}/bot.h
)
set(APP_SOURCES
   ${APP_FOLDER}/app.h
)

set(PROJECT_SOURCES ${API_SOURCES} ${BOT_SOURCES} ${APP_SOURCES})

add_executable(demo main.cpp ${PROJECT_SOURCES} )
add_executable(app ${APP_FOLDER}/main.cpp ${PROJECT_SOURCES} )

find_package(glfw3 REQUIRED)
target_link_libraries(demo glfw)
target_link_libraries(app glfw)
# add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
