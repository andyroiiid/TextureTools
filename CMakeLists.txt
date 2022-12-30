cmake_minimum_required(VERSION 3.24)
project(TextureTools)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_subdirectory(stb_image EXCLUDE_FROM_ALL)

set(STB_IMAGE_IO_PLUGIN_OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/plugins/imageformats)
add_library(StbImageIOPlugin SHARED
        StbImageIOHandler.cpp StbImageIOHandler.h
        StbImageIOPlugin.cpp StbImageIOPlugin.h)
target_link_libraries(StbImageIOPlugin
        Qt5::Core
        Qt5::Gui
        stb_image)
set_target_properties(StbImageIOPlugin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${STB_IMAGE_IO_PLUGIN_OUTPUT_DIR})
# Output plugin json
configure_file(StbImageIOPlugin.json ${STB_IMAGE_IO_PLUGIN_OUTPUT_DIR}/StbImageIOPlugin.json)

add_executable(TextureTools
        ImageList.cpp ImageList.h
        ImageView.cpp ImageView.h
        ImageWorkspace.cpp ImageWorkspace.h
        MainWindow.cpp MainWindow.h
        main.cpp)
target_link_libraries(TextureTools
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        stb_image)

set(DEBUG_SUFFIX)
if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
    set(DEBUG_SUFFIX "d")
endif ()
set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
    set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
    endif ()
endif ()
if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E make_directory
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
endif ()
foreach (QT_LIB Core Gui Widgets)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
endforeach (QT_LIB)

# Copy texconv.exe
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        "${PROJECT_SOURCE_DIR}/texconv.exe"
        "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
