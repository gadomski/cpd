add_library(Jsoncpp src/jsoncpp.cpp)
if(${BUILD_SHARED_LIBS})
	if(NOT TARGET jsoncpp_lib)
		message(FATAL_ERROR "Target jsoncpp_lib is not defined, but is required because cpd is building shared libs. Make sure `BUILD_SHARED_LIBS` is enabled in your jsoncpp installation.")
	else()
		set(jsoncpp_lib jsoncpp_lib)
	endif()
else()
	if(NOT TARGET jsoncpp_lib_static)
		message(FATAL_ERROR "Target jsoncpp_lib_static is not defined, but is required because cpd is building static libs. Make sure `BUILD_STATIC_LIBS` is enabled in your jsoncpp installation.")
	else()
		set(jsoncpp_lib jsoncpp_lib_static)
	endif()
endif()
target_link_libraries(Jsoncpp PUBLIC Library-C++ ${jsoncpp_lib})
set_target_properties(Jsoncpp PROPERTIES
    OUTPUT_NAME cpd-jsoncpp
    VERSION ${CPD_VERSION}
    SOVERSION ${CPD_SOVERSION}
    )
target_include_directories(Jsoncpp
    PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/components/jsoncpp/include>
    $<INSTALL_INTERFACE:include>
    )
target_compile_definitions(Jsoncpp PUBLIC CPD_WITH_JSONCPP)

install(TARGETS Jsoncpp DESTINATION lib EXPORT cpd-jsoncpp-targets)
install(DIRECTORY include/cpd DESTINATION include)
install(EXPORT cpd-jsoncpp-targets NAMESPACE Cpd:: DESTINATION lib/cmake/cpd)

if(WITH_TESTS)
    add_subdirectory(tests)
endif()
