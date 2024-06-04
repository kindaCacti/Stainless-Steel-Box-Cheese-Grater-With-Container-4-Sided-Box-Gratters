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
set(THIRD_PARTY_FOLDER ThirdParty)
set(API_SOURCES
   ${API_FOLDER}/board.h
   # ${API_FOLDER}/board.h
   ${API_FOLDER}/game.h
   ${API_FOLDER}/pieces.h
)
set(BOT_SOURCES
   ${BOT_FOLDER}/bot.h
)
set(APP_SOURCES
   ${APP_FOLDER}/app.h
   ${APP_FOLDER}/renderer.h
   ${APP_FOLDER}/renderer.cpp
   ${APP_FOLDER}/vertexBuffer.h
   ${APP_FOLDER}/vertexBuffer.cpp
   ${APP_FOLDER}/indexBuffer.h
   ${APP_FOLDER}/indexBuffer.cpp
   ${APP_FOLDER}/vertexBufferLayout.h
   ${APP_FOLDER}/vertexBufferLayout.cpp
   ${APP_FOLDER}/vertexArray.h
   ${APP_FOLDER}/vertexArray.cpp
   ${APP_FOLDER}/texture.h
   ${APP_FOLDER}/texture.cpp
)
set(THIRD_PARTY_SOURCES
   ${THIRD_PARTY_FOLDER}/stb_image.h
   ${THIRD_PARTY_FOLDER}/glad.h
   ${THIRD_PARTY_FOLDER}/khrplatform.h
   ${THIRD_PARTY_FOLDER}/glad.c
)

set(PROJECT_SOURCES
   ${API_SOURCES}
   ${BOT_SOURCES}
   ${APP_SOURCES}
   ${THIRD_PARTY_SOURCES}
)

add_executable(demo main.cpp ${PROJECT_SOURCES} )
add_executable(app ${APP_FOLDER}/main.cpp ${PROJECT_SOURCES} )

find_package(glfw3 REQUIRED)
set(PROJECT_LIBARIES glfw3.lib opengl32.lib glew32.lib)

target_link_libraries(demo ${PROJECT_LIBARIES})
target_link_libraries(app ${PROJECT_LIBARIES})
# add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
# target_link_libraries(testGoogle PUBLIC gtest_main)
