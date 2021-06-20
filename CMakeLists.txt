cmake_minimum_required(VERSION 2.8)

project(bzflag-model)

#set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(glm REQUIRED)

add_executable(bzflag-model-writer "main.cxx" "glwriter.cxx" "global.h" "common.cxx" "common.h" "glwriter.h" "glite.h" "AnimatedTreads.cxx" "high_barrel.cxx" "high_body.cxx" "high_ltread.cxx" "high_rtread.cxx" "high_turret.cxx" "TankGeometryMgr.cxx" "TankGeometryMgr.h")

