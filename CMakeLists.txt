cmake_minimum_required(VERSION 3.20)



set(namespace "syndesi")
project("Syndesicp"
    DESCRIPTION "Syndesi communication protocol library"
    VERSION 0.0.1
)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()


add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PRIVATE
        src/buffer.cpp
        src/framemanagercallbacks.cpp
        src/core.cpp
        src/frame.cpp
        src/framemanager.cpp
        src/network.cpp
        src/sdid.cpp
        src/syndesi_tools.cpp
        src/payloads.cpp
        src/framemanagercallbacks.cpp
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)


target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/user_config
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)


# No change to the install prefix


set(public_headers
    include/buffer.h
    include/callbacks.h
    include/core.h
    include/frame.h
    include/framemanager.h
    include/interfaces.h
    include/network.h
    include/payloads.h
    include/sdid.h
    include/syndesicp.h
    include/syndesi_tools.h    
)

set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${public_headers}")


# Set debug postfix (add "d" at the end of debug libraries name)
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

# No installation because the library cannot be installed "normally". There needs to be a configuration with the syndesi_config.h file



#file(GLOB LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
#file(GLOB LIB_HEADERS CONFIGURE_DEPENDS include/*.h)


#add_library(syndesicp SHARED ${LIB_SOURCES} ${LIB_HEADERS})
# add_library(syndesicp SHARED


# set_target_properties(syndesicp PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 PUBLIC_HEADER include/syndesicp.h LIBRARY_OUTPUT_DIRECTORY build)

# target_include_directories(syndesicp PRIVATE user_config)
# target_include_directories(syndesicp PRIVATE src)
# target_include_directories(syndesicp PRIVATE include)


# install(TARGETS syndesicp
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
# )
# install(
#     DIRECTORY ${CMAKE_SOURCE_DIR}/include/
#     DESTINATION include
#     FILES_MATCHING PATTERN "*.h*"
# )

#install(FILES ${CMAKE_BINARY_DIR}/syndesicp.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)