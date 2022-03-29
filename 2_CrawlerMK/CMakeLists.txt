cmake_minimum_required(VERSION 3.21)
project(Crawler)

set(CMAKE_CXX_STANDARD 17)

add_executable(Crawler main.cpp Crawler/Entity.cpp Crawler/Entity.hpp Crawler/Player.cpp Crawler/Player.hpp Crawler/Enemy.cpp Crawler/Enemy.hpp Crawler/Game.cpp Crawler/Game.hpp Domain/globals.hpp Crawler/Item.cpp Crawler/Item.hpp Crawler/Dictionary.cpp Crawler/Dictionary.hpp)
