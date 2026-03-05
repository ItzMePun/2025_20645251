cmake_minimum_required(VERSION 3.19)
project(exercise3 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)
find_package(VTK REQUIRED)


qt_standard_project_setup()

qt_add_executable(exercise3
    WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    ModelPart.h
    ModelPart.cpp
    ModelPartList.h
    ModelPartList.cpp
    icons.qrc
    optiondialog.h optiondialog.cpp optiondialog.ui

)

target_link_libraries(exercise3
    PRIVATE
        Qt::Core
        Qt::Widgets
        Qt6::Widgets
        ${VTK_LIBRARIES}
)

include(GNUInstallDirs)

install(TARGETS exercise3
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET exercise3
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

add_custom_target( VRBindings )
add_custom_command( TARGET VRBindings PRE_BUILD COMMAND ${CMAKECOMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/vrbindings ${CMAKE_BINARY_DIR})
