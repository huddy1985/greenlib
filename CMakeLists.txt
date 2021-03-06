cmake_minimum_required(VERSION 3.0)
project (GREENLIB)

find_package(PythonInterp 2.7 REQUIRED)
find_package(PythonLibs 2.7 REQUIRED)

include(GNUInstallDirs)

set(GreenLib_EXAMPLES_DIR ${CMAKE_INSTALL_DATADIR}/greensocs/examples)
set(GreenLib_DOCS_DIR ${CMAKE_INSTALL_DATADIR}/greensocs/docs)

include(FeatureSummary)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

function (add_test_compare name file1 file2)
	add_test(NAME ${name}
             COMMAND diff --strip-trailing-cr ${file1} ${file2})
endfunction()

# Compile and run the tests
add_custom_target(check COMMAND make compile_test COMMAND make test)

# Compile the test
add_custom_target(compile_test)
enable_testing()

# Test if the compilation/running/diff is good
add_custom_target(run_test COMMAND make test)

# Require SystemC
set(SystemC_USE_STATIC_LIBS ${USE_STATIC_SYSTEMC})
find_package(SystemC 2.3.0)
if(SystemC_FOUND)
    set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${SystemC_INCLUDE_DIRS})
else()
    message( FATAL_ERROR "SystemC library not found." )
endif()

# Require TLM
find_package( TLM )
if(TLM_FOUND)
    set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${TLM_INCLUDE_DIRS})
else()
    message( FATAL_ERROR "TLM library not found." )
endif()


# Require Boost

set(Boost_ADDITIONAL_VERSIONS 1.34 1.34.0 1.34.1)

find_package(Boost)
if(Boost_FOUND)
   set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS})
else()
   message(FATAL_ERROR "Boost library not found.")
endif()

# Require Python

if(NOT MINGW)
    if(DEFINED ENV{PYTHON_ROOT})
        set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} $ENV{PYTHON_ROOT})
    else()
        find_package(PythonLibs REQUIRED)
        set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${PYTHON_INCLUDE_DIRS})
    endif()
endif(NOT MINGW)

# Require Lua
if(DEFINED ENV{LUA_INCLUDE_DIR} AND DEFINED ENV{LUA_LIBRARIES})
  set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} $ENV{LUA_INCLUDE_DIR})
  link_directories($ENV{LUA_LIBRARIES})
else()
  find_package(Lua)
  if(LUA_FOUND)
    set(EXTERNAL_INCLUDE_DIRS ${EXTERNAL_INCLUDE_DIRS} ${LUA_INCLUDE_DIR})
    link_directories(${LUA_LIBRARIES})
  else()
    message(FATAL_ERROR "Lua library not found.")
  endif()
endif()

# Require SWIG
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

# GreenSocs library

set(GreenSocs_INCLUDE_DIRS "include")
set(GreenSocs_LIBRARY_DIRS ../../../lib)
set(GreenSocs_LIBRARIES pthread)

install(DIRECTORY include/
    DESTINATION include
)

# GreenControl

configure_file(
    greencontrol/examples/Makefile.defs.in
    Makefile.defs
    @ONLY
)

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greencontrol/include/)

install(DIRECTORY greencontrol/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greencontrol/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greencontrol
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greencontrol/docs/
        DESTINATION ${GreenLib_DOCS_DIR}/greencontrol
        PATTERN ".svn" EXCLUDE
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Makefile.defs
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greencontrol
)


# GreenSocket

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greensocket/include/)

install(DIRECTORY greensocket/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greensocket/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greensocket
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greensocket/doc/     # TODO: doc or docs?
        DESTINATION ${GreenLib_DOCS_DIR}/greensocket
        PATTERN ".svn" EXCLUDE
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Makefile.defs
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greensocket
)


# GsgpSocket

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} gsgpsocket/include/)

install(DIRECTORY gsgpsocket/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY gsgpsocket/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/gsgpsocket
        PATTERN ".svn" EXCLUDE
)

# install(DIRECTORY gsgpsocket/doc/     # TODO: doc or docs?
#         DESTINATION ${GreenLib_DOCS_DIR}/gsgpsocket
#         PATTERN ".svn" EXCLUDE
# )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Makefile.defs
        DESTINATION ${GreenLib_EXAMPLES_DIR}/gsgpsocket
)


# GreenRouter

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenrouter/include/)

install(DIRECTORY greenrouter/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greenrouter/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greenrouter
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greenrouter/docs/     # TODO: doc or docs?
        DESTINATION ${GreenLib_DOCS_DIR}/greenrouter
        PATTERN ".svn" EXCLUDE
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Makefile.defs
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greenrouter
)

# GreenSignalSocket

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greensignalsocket/include/)

install(DIRECTORY greensignalsocket/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greensignalsocket/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greensignalsocket
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greensignalsocket/docs/     # TODO: doc or docs?
        DESTINATION ${GreenLib_DOCS_DIR}/greensignalsocket
        PATTERN ".svn" EXCLUDE
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/Makefile.defs
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greensignalsocket
)

# Greenreg

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenreg/include/)
set(GreenSocs_LIB_DIRS ${GreenSocs_LIB_DIRS} ${PROJECT_SOURCE_DIR}/greenreg/lib/libgreenreg.a)

install(DIRECTORY greenreg/include/
        DESTINATION include
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greenreg/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greenreg
        PATTERN ".svn" EXCLUDE
)

install(DIRECTORY greenreg/doc/     # TODO: doc or docs?
        DESTINATION ${GreenLib_DOCS_DIR}/greenreg
        PATTERN ".svn" EXCLUDE
)

# Greenmessage

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenmessage/include/)

install(DIRECTORY greenmessage/include/
    DESTINATION include
)

install(DIRECTORY greenmessage/examples/
    DESTINATION ${GreenLib_EXAMPLES_DIR}/greenmessage
)

install(DIRECTORY greenmessage/docs/
    DESTINATION ${GreenLib_DOCS_DIR}/greenmessage
)

# Greenscript

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenscript/include/)

install(DIRECTORY greenscript/include/
        DESTINATION include
)

install(DIRECTORY greenscript/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/greenscript
)

install(DIRECTORY greenscript/docs/
        DESTINATION ${GreenLib_DOCS_DIR}/greenscript
)

# Greenmemory

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenmemory/include/)

install(DIRECTORY greenmemory/include/
        DESTINATION include
)

install(DIRECTORY greenmemory/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/memory
)

install(DIRECTORY greenmemory/docs/
        DESTINATION ${GreenLib_DOCS_DIR}/greenmemory
)

# Greensignalbus

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greensignalbus/include/)

install(DIRECTORY greensignalbus/include/
        DESTINATION include
)

install(DIRECTORY greensignalbus/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/signalbus
)

# GreenSerialSocket

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS}
     greenserialsocket/include/)

install(DIRECTORY greenserialsocket/include/
        DESTINATION include
)

install(DIRECTORY greenserialsocket/docs/
        DESTINATION ${GreenLib_DOCS_DIR}/greenserialsocket
)

# Greenthreads

set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} greenthreads/include/)

install(DIRECTORY greenthreads/include/
        DESTINATION include
)

install(DIRECTORY greenthreads/examples/
        DESTINATION ${GreenLib_EXAMPLES_DIR}/threads
)

install(DIRECTORY greenthreads/docs/
        DESTINATION ${GreenLib_DOCS_DIR}/greenthreads
)

# Include directory must use first the repository headers!
set(GreenSocs_INCLUDE_DIRS ${GreenSocs_INCLUDE_DIRS} ${EXTERNAL_INCLUDE_DIRS})

# Greensocs Library include directory (for example).
include_directories(${GreenSocs_INCLUDE_DIRS})
link_directories(${GreenSocs_LIB_DIRS})

# CXX flags for example or library compilation.
if(MINGW)
    set(CMAKE_CXX_FLAGS "-g -Wall -DSC_INCLUDE_DYNAMIC_PROCESSES -D_REENTRANT -pthread")
else(MINGW)
    set(CMAKE_CXX_FLAGS "-g -Wall -DSC_INCLUDE_DYNAMIC_PROCESSES -D_REENTRANT -fPIC")
endif(MINGW)

add_subdirectory(greensignalsocket EXCLUDE_FROM_ALL)
add_subdirectory(greenrouter EXCLUDE_FROM_ALL)
add_subdirectory(greenmemory EXCLUDE_FROM_ALL)
add_subdirectory(greensocket EXCLUDE_FROM_ALL)
add_subdirectory(greenmessage EXCLUDE_FROM_ALL)
add_subdirectory(gsgpsocket EXCLUDE_FROM_ALL)
add_subdirectory(greensignalbus EXCLUDE_FROM_ALL)
add_subdirectory(greenserialsocket EXCLUDE_FROM_ALL)
add_subdirectory(greenthreads)

# Compile greenreg library.
add_subdirectory(greenreg)

# Compile greenscript library
if(NOT MINGW)
    # FIX ME : add greenscript support with MINGW
    add_subdirectory(greenscript)
endif(NOT MINGW)

# build a CPack driven installer package
include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/greencontrol/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR "1")
set (CPACK_PACKAGE_VERSION_MINOR "0")
set (CPACK_PACKAGE_VERSION_PATCH "0")
include (CPack)

add_library(greenlib INTERFACE)
add_library(GreenLib::greenlib ALIAS greenlib)
target_include_directories(greenlib INTERFACE ${GreenSocs_INCLUDE_DIRS})
target_link_libraries(greenlib INTERFACE greenreg greenthreads)
