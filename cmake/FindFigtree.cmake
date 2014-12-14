###############################################################################
# Find Figtree
#
# This sets the following variables:
# FIGTREE_FOUND - True if Figtree was found.
# FIGTREE_INCLUDE_DIRS - Directories containing the Figtree include files.
# FIGTREE_LIBRARIES - Libraries needed to use figtree
# FIGTREE_DEFINITIONS - C flags used to build figtree

find_package(PkgConfig QUIET)
pkg_check_modules(PC_FIGTREE QUIET figtree)
set(FIGTREE_DEFINITIONS ${PC_FIGTREE_CFLAGS_OTHER})

find_path(FIGTREE_INCLUDE_DIR figtree.h
    HINTS ${PC_FIGTREE_INCLUDEDIR} ${PC_FIGTREE_INCLUDE_DIRS} "${FIGTREE_ROOT}" "$ENV{FIGTREE_ROOT}"
    PATHS "$ENV{PROGRAMFILES}/figtree" "$ENV{PROGRAMW6432}/figtree"
    PATH_SUFFIXES include)

find_library(FIGTREE_LIBRARY
    NAMES figtree
    HINTS ${PC_FIGTREE_LIBDIR} ${PC_FIGTREE_LIBRARY_DIRS} "${FIGTREE_ROOT}" "$ENV{FIGTREE_ROOT}"
    PATHS "$ENV{PROGRAMFILES}/figtree" "$ENV{PROGRAMW6432}/figtree"
    PATH_SUFFIXES lib)

set(FIGTREE_INCLUDE_DIRS ${FIGTREE_INCLUDE_DIR})
set(FIGTREE_LIBRARIES ${FIGTREE_LIBRARY})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Figtree DEFAULT_MSG FIGTREE_LIBRARY FIGTREE_INCLUDE_DIR)

mark_as_advanced(FIGTREE_INCLUDE_DIR FIGTREE_LIBRARY)

if(FIGTREE_FOUND)
    message(STATUS "Figtree found (include: ${FIGTREE_INCLUDE_DIRS}, lib: ${FIGTREE_LIBRARIES})")
endif(FIGTREE_FOUND)
