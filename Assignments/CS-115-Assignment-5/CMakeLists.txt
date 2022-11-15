cmake_minimum_required(VERSION 3.23)
project(CS_115_Assignment_5)

set(CMAKE_CXX_STANDARD 11)

#Main
add_executable(CS_115_Assignment_5 Location.cpp Node.cpp World.cpp Item.cpp ItemManager.cpp Game.cpp main.cpp)

#Part A Test
add_executable(Part_A_Test Location.cpp Item.cpp ItemManager.cpp TestHelper.cpp TestItemManager5.cpp)

#Part A.16 Test
add_executable(Part_A.16_Test Location.cpp Item.cpp ItemManager.cpp TestHelper.cpp TestItemManager5.cpp)
