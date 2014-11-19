###############################################################################
# Find gflags
#
# This sets the following variables:
# GFLAGS_FOUND - True if gflags was found.
# GFLAGS_INCLUDE_DIRS - Directories containing the gflags include files.
# GFLAGS_LIBRARIES - Libraries needed to use gflags
# GFLAGS_DEFINITIONS - C flags used to build gflags

find_package(PkgConfig QUIET)
pkg_check_modules(PC_GFLAGS QUIET gflags)
set(GFLAGS_DEFINITIONS ${PC_GFLAGS_CFLAGS_OTHER})

find_path(GFLAGS_INCLUDE_DIR gflags/gflags.h
    HINTS ${PC_GFLAGS_INCLUDEDIR} ${PC_GFLAGS_INCLUDE_DIRS} "${GFLAGS_ROOT}" "$ENV{GFLAGS_ROOT}"
    PATHS "$ENV{PROGRAMFILES}/gflags" "$ENV{PROGRAMW6432}/gflags"
    PATH_SUFFIXES include)

find_library(GFLAGS_LIBRARY
    NAMES gflags
    HINTS ${PC_GFLAGS_LIBDIR} ${PC_GFLAGS_LIBRARY_DIRS} "${GFLAGS_ROOT}" "$ENV{GFLAGS_ROOT}"
    PATHS "$ENV{PROGRAMFILES}/gflags" "$ENV{PROGRAMW6432}/gflags"
    PATH_SUFFIXES lib)

set(GFLAGS_INCLUDE_DIRS ${GFLAGS_INCLUDE_DIR})
set(GFLAGS_LIBRARIES ${GFLAGS_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(gflags DEFAULT_MSG GFLAGS_LIBRARY GFLAGS_INCLUDE_DIR)

mark_as_advanced(GFLAGS_INCLUDE_DIR GFLAGS_LIBRARY)

if(GFLAGS_FOUND)
    message(STATUS "gflags found (include: ${GFLAGS_INCLUDE_DIRS}, lib: ${GFLAGS_LIBRARIES})")
endif(GFLAGS_FOUND)
