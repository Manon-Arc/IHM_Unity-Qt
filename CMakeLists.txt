cmake_minimum_required(VERSION 3.5)

project(IHM VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets
        LinguistTools
        Protobuf
        Grpc
)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools )
qt_standard_project_setup()

find_library(SQLITE3_LIBRARY sqlite3)

find_package(PkgConfig REQUIRED)
pkg_search_module(SODIUM REQUIRED libsodium)

set(TS_FILES IHM_en_US.ts)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        ${TS_FILES}
        client.cpp
        client.h
        connection.cpp
        connection.h
        connection.ui
        com.grpc.pb.h
        com.grpc.pb.cc
        com.pb.h
        com.pb.cc
        register.cpp
        register.h
        register.ui
        hash.cpp
        hash.h
        projects.cpp
        projects.h
        projects.ui
        createproject.cpp
        createproject.h
        createproject.ui
        db.cpp
        db.h
)


find_package(gRPC CONFIG REQUIRED)



if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(IHM
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            connection.h connection.cpp

    )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET IHM APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else ()
    if (ANDROID)
        add_library(IHM SHARED
                ${PROJECT_SOURCES}
        )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else ()
        add_executable(IHM
                ${PROJECT_SOURCES}
        )
    endif ()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif ()

target_link_libraries(IHM PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        gRPC::grpc++
        ${SQLITE3_LIBRARY}
        ${SODIUM_LIBRARIES}
)
target_include_directories(IHM PRIVATE ${SODIUM_INCLUDE_DIRS})


# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.IHM)
endif ()
set_target_properties(IHM PROPERTIES
        ${BUNDLE_ID_OPTION}
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS IHM
        BUNDLE DESTINATION ..
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(IHM)
endif ()
