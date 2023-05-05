cmake_minimum_required(VERSION 3.25)

project(spreadsheet VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()
#set(CMAKE_AUTORCC ON)

qt_add_executable(spreadsheet)

target_include_directories( spreadsheet PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

target_sources(spreadsheet
    PRIVATE
        main.cpp

        window.h window.cpp window.ui

        sp.qrc

    PUBLIC

)

set_target_properties(spreadsheet PROPERTIES  AUTORCC on)  #enable ResourCe Compiler

target_compile_features(spreadsheet PRIVATE cxx_std_20)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET spreadsheet APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

target_link_libraries(spreadsheet
    PRIVATE
        Qt6::Widgets
)


