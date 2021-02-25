cmake_minimum_required(VERSION 3.1)

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


set(${PROJECT_NAME}_HEADERS
        main_window.h
        image_label.h
        )

set(${PROJECT_NAME}_SOURCES
        main.cpp
        main_window.cpp
        image_label.cpp
        )

set(${PROJECT_NAME}_FORMS
        main_window.ui
        )

if (WIN32 OR MSVC)
    add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_FORMS})
    # if you want to get rid of the (system) console, use
    #	add_executable( ${PROJECT_NAME} WIN32 ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_FORMS} ${${PROJECT_NAME}_RESOURCES} )
    #       target_link_libraries( ${PROJECT_NAME} Qt5::WinMain )
elseif (APPLE)
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_FORMS})
else ()
    add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_FORMS})
endif ()

set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "applications")

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
target_compile_definitions(${PROJECT_NAME} PRIVATE QT_DEPRECATED_WARNINGS)

if (MSVC)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CRT_SECURE_NO_DEPRECATE)
endif ()

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Gui Qt5::Widgets)