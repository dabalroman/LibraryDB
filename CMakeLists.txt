cmake_minimum_required(VERSION 3.14)
project(LibraryDB)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS -static)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(LibraryDB
        main.cpp
        Record.hpp
        Record.cpp
        DataKeeper.hpp
        DataKeeper.cpp
        Utils.hpp
        Utils.cpp
        ConsoleRenderer/Console.cpp ConsoleRenderer/Console.hpp ConsoleRenderer/ConsoleRenderer.cpp ConsoleRenderer/ConsoleRenderer.hpp ConsoleRenderer/Renderable.cpp ConsoleRenderer/Renderable.hpp ConsoleRenderer/Renderables/TextField.cpp ConsoleRenderer/Renderables/TextField.hpp ConsoleRenderer/Buffer.hpp ConsoleRenderer/Buffer.cpp DataList.cpp DataList.hpp ConsoleRenderer/Renderables/DataListRenderable.cpp ConsoleRenderer/Renderables/DataListRenderable.hpp ConsoleRenderer/Renderables/InputField.cpp ConsoleRenderer/Renderables/InputField.hpp ConsoleRenderer/Screen.cpp ConsoleRenderer/Screen.hpp Screens/ListScreen.cpp Screens/ListScreen.hpp Screens/DetailsScreen.cpp Screens/DetailsScreen.hpp)