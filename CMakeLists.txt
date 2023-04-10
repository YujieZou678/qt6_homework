cmake_minimum_required(VERSION 3.25)

project(eventhandling VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(eventhandling)

target_sources(eventhandling
    PRIVATE
        main.cpp
        window.cpp
        window.h
        label.h label.cpp
        button.h button.cpp
        
    PUBLIC
        
)

target_compile_features(eventhandling PRIVATE cxx_std_20)

# Define target properties for Android with Qt 6 as:
#    set_property(TARGET eventhandling APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation


target_link_libraries(eventhandling 
    PRIVATE 
        Qt6::Widgets
)












































# set_target_properties(eventhandling PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# install(TARGETS eventhandling
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(eventhandling)
# endif()





#qt_add_executable(eventhandling)  //Creates and finalizes an application target of a platform-specific type.
#This command performs the following tasks:

#    1. Create a CMake target of the appropriate type for the target platform.
#    2. Link the target to the Qt::Core library.
#    3. Handle finalization of the CMake target.



# qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)  set(CMAKE_AUTORCC ON)

