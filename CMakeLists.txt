cmake_minimum_required(VERSION 3.7)
project(sfml_learn)

set(CMAKE_CXX_STANDARD 11)

set(SFML_HEADER_PATH "/usr/local/lib/SFML-2.4.2/include")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(SFML_LIB_PATH "/usr/local/lib/SFML-2.4.2/build/lib")

include_directories(${SFML_HEADER_PATH})

#########################################################
#set(SOURCE_FILES
#        main.cpp
#        shapes.cpp
#        Gobang.cpp)
#add_executable(sfml_learn ${SOURCE_FILES})
#target_link_libraries(sfml_learn
#        ${SFML_LIB_PATH}/libsfml-window.2.4.2.dylib
#        ${SFML_LIB_PATH}/libsfml-system.2.4.2.dylib
#        ${SFML_LIB_PATH}/libsfml-graphics.2.4.2.dylib)
#########################################################

#########################################################
#               Plane Evade Game                        #
#set(PLANE_SOURCE_FILES                                 #
#        plane_evade/main.cpp                           #
#        plane_evade/game.cpp                           #
#        plane_evade/components.cpp)                    #
#add_executable(plane_game ${PLANE_SOURCE_FILES})       #
#target_link_libraries(plane_game                       #
#        ${SFML_LIB_PATH}/libsfml-window.2.4.2.dylib    #
#        ${SFML_LIB_PATH}/libsfml-system.2.4.2.dylib    #
#        ${SFML_LIB_PATH}/libsfml-graphics.2.4.2.dylib  #
#        ${SFML_LIB_PATH}/libsfml-audio.2.4.2.dylib)    #
#########################################################

#########################################################
#                 Gobang Game                           #
#set(GOBANG_SOURCE_FILES                                #
#        gobang/main.cpp                                #
#        gobang/Game.cpp                                #
#        gobang/ResourceHolder.cpp                      #
#        gobang/GobangBoard.cpp)                        #
#add_executable(gobang ${GOBANG_SOURCE_FILES})          #
#target_link_libraries(gobang                           #
#        ${SFML_LIB_PATH}/libsfml-window.2.4.2.dylib    #
#        ${SFML_LIB_PATH}/libsfml-system.2.4.2.dylib    #
#        ${SFML_LIB_PATH}/libsfml-graphics.2.4.2.dylib  #
#        ${SFML_LIB_PATH}/libsfml-audio.2.4.2.dylib)    #
#########################################################

set(PLANE_FIGHT_SOURCE_FILES
        plane_fight/main.cpp
        plane_fight/Game.cpp
        plane_fight/entity/Entity.cpp
        plane_fight/entity/Plane.cpp)
add_executable(pfgame ${PLANE_FIGHT_SOURCE_FILES})
target_link_libraries(pfgame
        ${SFML_LIB_PATH}/libsfml-window.2.4.2.dylib
        ${SFML_LIB_PATH}/libsfml-system.2.4.2.dylib
        ${SFML_LIB_PATH}/libsfml-graphics.2.4.2.dylib
        ${SFML_LIB_PATH}/libsfml-audio.2.4.2.dylib)




