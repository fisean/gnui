cmake_minimum_required(VERSION 3.10)
project(gnui VERSION 0.0.1 DESCRIPTION "Core GNUI library")

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SHARED_LINKER_FLAGS "-pthread")
include(GNUInstallDirs)
file(GLOB CORE_SRCS src/*.cpp)
set(SRCS ${SRCS} ${CORE_SRCS})
file(GLOB MY_HEADERS gnui/*.h)
install(FILES ${CORE_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gnui)
set(HEADERS ${HEADEARS} ${CORE_HEADERS})
set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR})
install(FILES gnui/config.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gnui)

enable_testing()
add_custom_target(build-tests)

find_package(PkgConfig REQUIRED)

configure_file(gnui.pc.in gnui.pc @ONLY)
if (PKG_CONFIG_INSTALL_PATH)
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gnui.pc DESTINATION ${CMAKE_INSTALL_PREFIX}${PKG_CONFIG_INSTALL_PATH})
elseif (${CMAKE_SYSTEM_NAME} STREQUAL "FreeBSD")
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gnui.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/libdata/pkgconfig)
else()
    install(FILES ${CMAKE_CURRENT_BINARY_DIR}/gnui.pc DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/pkgconfig)
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}/include ${MY_INCLUDE_DIRS})
link_directories(${CMAKE_INSTALL_PREFIX}/lib ${MY_LIBRARY_DIRS})

option(XORG "Xorg C binding" ON)
if (XORG)
    set(DISPLAY_XORG 1)
    pkg_check_modules(X11 REQUIRED x11)
    set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${X11_INCLUDE_DIRS})
    set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${X11_LIBRARY_DIRS})
    set(MY_LIBRARIES ${MY_LIBRARIES} ${X11_LIBRARIES})
    pkg_check_modules(XKB REQUIRED xkbcommon-x11)
    set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${XKB_INCLUDE_DIRS})
    set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${XKB_LIBRARY_DIRS})
    set(MY_LIBRARIES ${MY_LIBRARIES} ${XKB_LIBRARIES})
    pkg_check_modules(XFT REQUIRED xft)
    set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${XFT_INCLUDE_DIRS})
    set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${XFT_LIBRARY_DIRS})
    set(MY_LIBRARIES ${MY_LIBRARIES} ${XFT_LIBRARIES})
    pkg_check_modules(FONTCONFIG REQUIRED fontconfig)
    set(MY_INCLUDE_DIRS ${MY_INCLUDE_DIRS} ${FONTCONFIG_INCLUDE_DIRS})
    set(MY_LIBRARY_DIRS ${MY_LIBRARY_DIRS} ${FONTCONFIG_LIBRARY_DIRS})
    set(MY_LIBRARIES ${MY_LIBRARIES} ${FONTCONFIG_LIBRARIES})
    file(GLOB XORG_SRCS src/xorg/*.cpp)
    file(GLOB XORG_HEADERS gnui/xorg/*.h)
    set(SRCS ${SRCS} ${XORG_SRCS})
    install(FILES ${XORG_HEADERS} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/gnui/xorg)
    set(MY_HEADERS ${MY_HEADEARS} ${XORG_HEADERS})
endif()


option(BUILD_SHARED "Build shared library (libgnui.so)" ON)
if (BUILD_SHARED)
    add_library(
        gnui
        SHARED
        ${SRCS} ${HEADERS}
    )
    add_dependencies(build-tests gnui)
    target_link_libraries(gnui ${MY_LIBRARIES})
    target_include_directories(gnui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${MY_INCLUDE_DIRS})
    install(TARGETS gnui)
endif()

option(BUILD_STATIC "Build static library (libgnui.a)" OFF)
if (BUILD_STATIC)
    add_library(
        gnui-static
        STATIC
        ${SRCS} ${HEADERS}
    )
    add_dependencies(build-tests gnui-static)
    if (NOT ${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
        set_target_properties(gnui-static PROPERTIES OUTPUT_NAME gnui)
    endif()
    target_link_libraries(gnui-static ${MY_LIBRARIES})
    target_include_directories(gnui-static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${MY_INCLUDE_DIRS})
    install(TARGETS gnui-static)
endif()


if (NOT BUILD_SHARED AND NOT BUILD_STATIC)
    message(FATAL_ERROR "You have to build at least one: SHARED or STATIC library")
endif()

function(register_test module name)
    add_executable(test-${module}-${name} EXCLUDE_FROM_ALL tests/${module}/${name}.cpp)
    target_link_directories(test-${module}-${name} PUBLIC ${CMAKE_CURRENT_BINARY_DIR} ${MY_LIBRARY_DIRS})
    target_link_libraries(test-${module}-${name} gnui ${MY_LIBRARIES})
    target_include_directories(test-${module}-${name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_INSTALL_PREFIX}/include ${MY_INCLUDE_DIRS})
    add_dependencies(build-tests test-${module}-${name})
    add_test(NAME ${module}-${name} COMMAND ./test-${module}-${name})
endfunction(register_test)

configure_file(config.h.in gnui/config.h)

if (XORG)
    register_test(xorg cli)
    register_test(xorg xorg)
endif()
