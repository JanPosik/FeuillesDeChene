cmake_minimum_required(VERSION 3.19)
project(feuilles_de_chene LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

add_subdirectory(../core ${CMAKE_CURRENT_BINARY_DIR}/core)

qt_add_executable(feuilles_de_chene
    WIN32 MACOSX_BUNDLE
    main.cpp
    application.cpp
    application.h
    application.ui
)

target_link_libraries(feuilles_de_chene
    PRIVATE
        Qt::Core
        Qt::Widgets
	core
)

include(GNUInstallDirs)

install(TARGETS feuilles_de_chene
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET feuilles_de_chene
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
