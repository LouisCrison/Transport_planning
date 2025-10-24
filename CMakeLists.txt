cmake_minimum_required(VERSION 3.5)

project(Transport_planning LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_SOURCE_DIR}/forms
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/source
)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt6 COMPONENTS Widgets Sql REQUIRED)




add_executable(Transport_planning
    source/main.cpp
    source/mainwindow.cpp
    source/addchauffeur.cpp
    source/displaychauffeurs.cpp
    source/displaycamions.cpp
    source/displaytournee.cpp
    source/addtournee.cpp
    source/addevent.cpp

    headers/mainwindow.h
    headers/addchauffeur.h
    headers/displaychauffeurs.h
    headers/displaycamions.h
    headers/displaytournee.h
    headers/addtournee.h
    headers/addevent.h

    forms/addevent.ui
    forms/addchauffeur.ui
    forms/addtournee.ui
    forms/displaycamions.ui
    forms/displaychauffeurs.ui
    forms/displaytournee.ui
    forms/mainwindow.ui
)


target_link_libraries(Transport_planning
    PRIVATE
        Qt6::Widgets
        Qt6::Sql)

    target_include_directories(Transport_planning
    PRIVATE
        ${CMAKE_SOURCE_DIR}/headers
        ${CMAKE_SOURCE_DIR}/source)
