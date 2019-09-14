cmake_minimum_required(VERSION 3.0)

project(sflcars LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)

# Define sources and executable
set(PROJECT_NAME "SFLCARS")
set(CMAKE_DEBUG_POSTFIX "-d")
add_executable(${PROJECT_NAME} ./src/SFLCARS.hpp ./src/SFLCARS.cpp ./src/utility/RoundRectangle.hpp ./src/utility/RoundRectangle.cpp ./src/interface/Bar.hpp ./src/interface/Bar.cpp ./src/interface/Button.hpp ./src/interface/Button.cpp ./src/interface/Element.hpp ./src/interface/Element.cpp ./src/interface/IconButton.hpp ./src/interface/IconButton.cpp ./src/interface/TextButton.hpp ./src/interface/TextButton.cpp ./src/main.cpp ./src/interface/Display.hpp ./src/interface/Display.cpp ./src/interface/TextBar.hpp ./src/interface/TextBar.cpp ./src/interface/Spacer.hpp ./src/interface/Spacer.cpp ./src/interface/String.hpp ./src/interface/String.cpp)

# Detect and add SFML
# only do this on unix, because I don't know if it works on other platforms and toolchains
# I know it doesn't work on Windows for Visual Studio
if(UNIX)
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
	find_package(SFML 2 REQUIRED network audio graphics window system)

	if(SFML_FOUND)
	  target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
	endif()

	target_link_libraries(${PROJECT_NAME} stdc++fs)
elseif(WIN32)
	target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/SFML/include)
	
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-graphics-s${CMAKE_DEBUG_POSTFIX}.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-window-s${CMAKE_DEBUG_POSTFIX}.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-system-s${CMAKE_DEBUG_POSTFIX}.lib)
	target_link_libraries(${PROJECT_NAME} opengl32.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/freetype.lib)
	target_link_libraries(${PROJECT_NAME} winmm.lib)
	target_link_libraries(${PROJECT_NAME} gdi32.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-audio-s${CMAKE_DEBUG_POSTFIX}.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/openal32.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/flac.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/vorbisenc.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/vorbisfile.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/vorbis.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/ogg.lib)
	target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/SFML/lib/sfml-network-s${CMAKE_DEBUG_POSTFIX}.lib)
	target_link_libraries(${PROJECT_NAME} ws2_32.lib)
	
	target_compile_definitions(${PROJECT_NAME} PRIVATE SFML_STATIC)
endif()

# I don't know how to use CMake.
# If you want it in debug, create the config using -DCMAKE_BUILD_TYPE=Release
# I don't know why it's reversed, but it is, so fuck me I guess.
message("This is as close as I can get it:")
message("If you want to compile in Debug, set CMAKE_BUILD_TYPE to Release.")
message("If you want to compile in Release, set CMAKE_BUILD_TYPE to Debug.")

# This only shows up in release, for whatever reason, so there's no real reason to use it. It might be useful later, so I'll keep it here.
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DIS_DEBUG_ENABLED")
