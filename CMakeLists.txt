cmake_minimum_required(VERSION 3.12)
project( okteta )

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
        "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options("$<$<CONFIG:DEBUG>:-Wall;-Wextra;-pedantic>")
endif()

find_package(KDE4 REQUIRED)
include(KDE4Defaults)
include(MacroLibrary)

add_definitions( ${QT_DEFINITIONS} ${KDE4_DEFINITIONS})
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_BINARY_DIR}
    ${KDE4_INCLUDES}
)

# control build scope
# TODO: examples and templates not internal need headers and libs as installed
# so they can be only build after the installation was done
# How to handle this best, as in: they are per default always build after an install?
# set( KASTEN_BUILD_EXAMPLES  NOT OMIT_EXAMPLES )
# set( OKTETA_BUILD_EXAMPLES  NOT OMIT_EXAMPLES )
set( KASTEN_BUILD_INTERNAL_EXAMPLES  NOT OMIT_INTERNAL_EXAMPLES )
set( OKTETA_BUILD_INTERNAL_EXAMPLES  NOT OMIT_INTERNAL_EXAMPLES )

# set( KASTEN_BUILD_TEMPLATES NOT SKIPTEMPLATES )
# set( OKTETA_BUILD_TEMPLATES NOT SKIPTEMPLATES )
set( KASTEN_BUILD_INTERNAL_TEMPLATES NOT OMIT_INTERNAL_TEMPLATES )
set( OKTETA_BUILD_INTERNAL_TEMPLATES NOT OMIT_INTERNAL_TEMPLATES )

add_definitions(
    -DQT_USE_FAST_CONCATENATION
    -DQT_USE_FAST_OPERATOR_PLUS
)
add_definitions(-DKDE_NO_DEPRECATED)

# switch between no cast to/from ascii and a warning about it
if (KDE4_ASCII_CAST)
add_definitions(
    -DQT_ASCII_CAST_WARNINGS
)
else (KDE4_ASCII_CAST)
add_definitions(
    -DQT_NO_CAST_TO_ASCII
    -DQT_NO_CAST_FROM_ASCII
)
endif (KDE4_ASCII_CAST)

# helper libs
add_subdirectory( libs )
add_subdirectory( doc )

set( OKTETALIBS_MAJOR_VERSION 0 )
set( OKTETALIBS_MINOR_VERSION 8 )
set( OKTETALIBS_PATCHLEVEL_VERSION 1 )
set( OKTETALIBS_VERSION "${OKTETALIBS_MAJOR_VERSION}.${OKTETALIBS_MINOR_VERSION}.${OKTETALIBS_PATCHLEVEL_VERSION}" )
set( OKTETALIBS_ABI_VERSION 1 )
set( OKTETALIBS_INCLUDE_INSTALL_DIR  ${INCLUDE_INSTALL_DIR}/okteta${OKTETALIBS_ABI_VERSION} )
set( OKTETALIBS_CCINCLUDE_INSTALL_DIR  ${INCLUDE_INSTALL_DIR}/KDE/Okteta${OKTETALIBS_ABI_VERSION} )

set( oktetacore_LIB  oktetacore )
set( oktetagui_LIB   oktetagui )
set( oktetacore_LIB_NAME  okteta${OKTETALIBS_ABI_VERSION}core )
set( oktetagui_LIB_NAME   okteta${OKTETALIBS_ABI_VERSION}gui )

set( OKTETALIBS_LIB_SOVERSION ${OKTETALIBS_ABI_VERSION} )
set( OKTETALIBS_LIB_VERSION ${OKTETALIBS_VERSION} )

# Okteta libs
add_subdirectory( core )
add_subdirectory( gui )
add_subdirectory( designer )

# Okteta Kasten components
add_subdirectory( kasten )
# special mimetypes
add_subdirectory( mimetypes )

# programs and parts for desktop
add_subdirectory( parts )
add_subdirectory( program )

macro_display_feature_log()
