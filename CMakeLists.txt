cmake_minimum_required(VERSION 3.10)
project(learnopengl)
set(TARGET_NAME run)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)
# Qt requirements
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(QT_COMPONENTS Core Gui Widgets OpenGL)
find_package(Qt5 COMPONENTS ${QT_COMPONENTS} REQUIRED)
# Setup executable target
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.h)
add_executable(${TARGET_NAME} ${SOURCE_FILES})
foreach(QT_COMPONENT ${QT_COMPONENTS})
    target_link_libraries(${TARGET_NAME} Qt5::${QT_COMPONENT})
endforeach()
# Copy dlls for Qt
foreach(QT_COMPONENT ${QT_COMPONENTS})
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:Qt5::${QT_COMPONENT}>
        $<TARGET_FILE_DIR:${TARGET_NAME}>)
endforeach()
