cmake_minimum_required(VERSION 3.11.0)
project(cheese VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

SET(GCC_COVERAGE_COMPILE_FLAGS "-Wno-int-to-pointer-cast")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include(FetchContent)
FetchContent_Declare( 
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(API_FOLDER CheesyApi)
set(BOT_FOLDER CheesyBot)
set(ENGINE_FOLDER CheesyEngine)
set(APP_FOLDER CheesyApp)
set(THIRD_PARTY_FOLDER ThirdParty)

set(API_SOURCES
   ${API_FOLDER}/board.h
   ${API_FOLDER}/board.cpp
   ${API_FOLDER}/game.h
   ${API_FOLDER}/game.cpp
   ${API_FOLDER}/pieces.h
   ${API_FOLDER}/pieces.cpp
)
set(BOT_SOURCES
   ${BOT_FOLDER}/bot.h
)
set(ENGINE_SOURCES
   ${ENGINE_FOLDER}/renderer.h
   ${ENGINE_FOLDER}/renderer.cpp
   ${ENGINE_FOLDER}/vertexBuffer.h
   ${ENGINE_FOLDER}/vertexBuffer.cpp
   ${ENGINE_FOLDER}/indexBuffer.h
   ${ENGINE_FOLDER}/indexBuffer.cpp
   ${ENGINE_FOLDER}/vertexBufferLayout.h
   ${ENGINE_FOLDER}/vertexBufferLayout.cpp
   ${ENGINE_FOLDER}/vertexArray.h
   ${ENGINE_FOLDER}/vertexArray.cpp
   ${ENGINE_FOLDER}/shader.h
   ${ENGINE_FOLDER}/shader.cpp
   ${ENGINE_FOLDER}/texture.h
   ${ENGINE_FOLDER}/texture.cpp
   ${ENGINE_FOLDER}/imageRect.h
   ${ENGINE_FOLDER}/imageRect.cpp
)
set(APP_SOURCES
   ${APP_FOLDER}/appElement.h
   ${APP_FOLDER}/app.h
   ${APP_FOLDER}/app.cpp
)
set(THIRD_PARTY_SOURCES
   ${THIRD_PARTY_FOLDER}/stb_image/stb_image.h
   ${THIRD_PARTY_FOLDER}/stb_image/stb_image.cpp
)

set(PROJECT_SOURCES
${API_SOURCES}
${BOT_SOURCES}
${ENGINE_SOURCES}
${APP_SOURCES}
${THIRD_PARTY_SOURCES}
)

set(DEMO_SOURCES
${API_SOURCES}
${BOT_SOURCES}
)

set(TEST_SOURCES
${API_FOLDER}/testApi.cpp
${BOT_FOLDER}/testBot.cpp
)

include_directories(${THIRD_PARTY_FOLDER} ${ENGINE_FOLDER} ${API_FOLDER} ${BOT_FOLDER})

add_executable(demo main.cpp ${DEMO_SOURCES} )
add_executable(app ${APP_FOLDER}/main.cpp ${PROJECT_SOURCES} )

find_package(glfw3 REQUIRED)
set(PROJECT_LIBARIES glfw3.lib opengl32.lib glew32.lib)

# target_link_libraries(demo ${PROJECT_LIBARIES})
target_link_libraries(app ${PROJECT_LIBARIES})
add_executable(testGoogle ${TEST_SOURCES} ${DEMO_SOURCES})
target_link_libraries(testGoogle PUBLIC gtest_main)