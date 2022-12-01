cmake_minimum_required(VERSION 3.23)
project(CS_115_Assignment_5)

set(CMAKE_CXX_STANDARD 11)

#Main
add_executable(CS_115_Assignment_5 Location.cpp Node.cpp World.cpp
        Item.cpp ItemManager.cpp ScoreTable.cpp Game.cpp main.cpp)

#Part A Test
add_executable(Part_A_Test Location.cpp Item.cpp ItemManager.cpp TestHelper.cpp TestItemManager5.cpp)

#Part A.16 Test
add_executable(Part_A.16_Test Location.cpp Item.cpp ItemManager.cpp TestHelper.cpp TestItemManager5.cpp)

#Part B Test
add_executable(Part_B_Test ScoreTable.cpp TestHelper.cpp TestElement5.cpp)

#Part C Test
add_executable(Part_C_Test ScoreTable.cpp TestHelper.cpp TestScoreTable5.cpp)