add_library(Jsoncpp src/jsoncpp.cpp)
target_link_libraries(Jsoncpp PUBLIC Library-C++ jsoncpp_lib)
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
