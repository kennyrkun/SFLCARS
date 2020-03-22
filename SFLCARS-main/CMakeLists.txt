CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_REQUIRED_STANDARD ON)
SET(CMAKE_DEBUG_POSTFIX "-d")

SET(PROJECT_NAME "sflcars-main")
PROJECT(${PROJECT_NAME} LANGUAGES CXX)

SET(HEADERS Alarm.hpp AlarmEditState.hpp AlarmListState.hpp AlarmState.hpp AnimationManager.hpp AppEngine.hpp AppState.hpp InitialiseState.hpp IntercomState.hpp Interpolate.hpp Listener.hpp LoginState.hpp MainMenuState.hpp MessageSendState.hpp StandbyState.hpp SystemMonitorState.hpp UserAccount.hpp UserAccountManager.hpp UserSettings.hpp)
SET(SOURCES Alarm.cpp AlarmEditState.cpp AlarmListState.cpp AlarmState.cpp AnimationManager.cpp AppEngine.cpp InitialiseState.cpp IntercomState.cpp Interpolate.cpp Listener.cpp LoginState.cpp main.cpp MainMenuState.cpp MessageSendState.cpp StandbyState.cpp SystemMonitorState.cpp UserAccount.cpp UserAccountManager.cpp)
ADD_EXECUTABLE(${PROJECT_NAME} ${HEADERS} ${SOURCES})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFML/include)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} sfml-graphics sfml-audio sfml-network sfml-window sfml-system -L"../SFML/lib")

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFLCARS-interface/)
TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC ../SFLCARS-utility/)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} sflcars-interface -L"../SFLCARS-interface")
TARGET_LINK_LIBRARIES(${PROJECT_NAME} sflcars-utility -L"../SFLCARS-utility")

TARGET_LINK_LIBRARIES(${PROJECT_NAME} stdc++fs)

