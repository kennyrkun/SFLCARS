CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_REQUIRED_STANDARD ON)
SET(CMAKE_DEBUG_POSTFIX "-d")

SET(PROJECT_NAME "sflcars-interface")
PROJECT(${PROJECT_NAME} LANGUAGES CXX)

SET(HEADERS ResourceManager.hpp Bar.hpp IconButton.hpp RoundRectangle.hpp Spacer.hpp Button.hpp Display.hpp Element.hpp InputBox.hpp Layout.hpp String.hpp TextBar.hpp Theme.hpp)
SET(SOURCES ResourceManager.cpp Bar.cpp IconButton.cpp RoundRectangle.cpp Spacer.cpp Button.cpp Display.cpp Element.cpp InputBox.cpp Layout.cpp String.cpp TextBar.cpp Theme.cpp)
ADD_LIBRARY(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFML/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system -L"../SFML/lib")

