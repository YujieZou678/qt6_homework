cmake_minimum_required(VERSION 3.25)

project(untitled VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.4 REQUIRED COMPONENTS Quick )

qt_standard_project_setup()

qt_add_executable(appuntitled)

target_sources(appuntitled
    PRIVATE
        main.cpp

    PUBLIC
        
)

qt_add_qml_module(appuntitled
    URI untitled
    VERSION 1.0
    QML_FILES 
        Main.qml
        myjs.js

)

set_target_properties(appuntitled PROPERTIES AUTORCC on)

target_compile_features(appuntitled PRIVATE cxx_std_20)

target_link_libraries(appuntitled
    PRIVATE 
        Qt6::Quick

)













































# set_target_properties(appuntitled PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
# 
# 
# install(TARGETS appuntitled
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})





#qt_add_executable(untitled)  //Creates and finalizes an application target of a platform-specific type.
#This command performs the following tasks:
#    1. Create a CMake target of the appropriate type for the target platform.
#    2. Link the target to the Qt::Core library.
#    3. Handle finalization of the CMake target.



# qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)


