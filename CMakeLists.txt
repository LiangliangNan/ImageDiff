cmake_minimum_required(VERSION 3.1)

if (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.12" CACHE STRING "Minimum OS X deployment version" FORCE)
    message(STATUS "Minimum OS X deployment version: ${CMAKE_OSX_DEPLOYMENT_TARGET}")
endif ()


get_filename_component(PROJECT_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${PROJECT_NAME})


include(./cmake/UseQt5.cmake)
if (NOT QT5_FOUND)
    message(WARNING "${PROJECT_NAME} requires Qt but Qt was not found. You can set 'Qt5_DIR' to the "
            "directory containing 'Qt5Config.cmake' or 'qt5-config.cmake'. "
            "Optionally, you can set the Qt5 root directory 'QT5_ROOT_PATH' to the directory "
            "containing the 'bin' folder.")
    return()
endif ()

add_executable(${PROJECT_NAME}
        main_window.h
        image_label.h
        main.cpp
        main_window.cpp
        image_label.cpp
        main_window.ui
        )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)

if (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
            MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME}
            MACOSX_BUNDLE TRUE
            MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/Mac/ImageDiff.plist"
            MACOSX_BUNDLE_GUI_IDENTIFIER "liangliang.nan@gmail.com"
            )
endif ()