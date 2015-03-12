function(cpd_configure_target target)
    set(one_value_args NAME EXTRA_COMPILE_FLAGS)
    cmake_parse_arguments(TARGET "" "${one_value_args}" "" ${ARGN})

    set(compile_flags " -std=c++11 -Wall -Werror -pedantic")
    set_property(TARGET ${target} APPEND_STRING PROPERTY COMPILE_FLAGS "${compile_flags} ${TARGET_EXTRA_COMPILE_FLAGS}")

    set_target_properties(${target} PROPERTIES
        VERSION ${CPD_VERSION}
        SOVERSION ${CPD_SOVERSION}
        )

    if (TARGET_NAME)
        set_property(TARGET ${target} PROPERTY OUTPUT_NAME ${TARGET_NAME})
    endif()

    if(ARMA_64BIT_WORD)
        target_compile_definitions(cpd-lib PUBLIC ARMA_64BIT_WORD)
    endif()
    if(ARMA_NO_DEBUG)
        target_compile_definitions(cpd-lib PUBLIC ARMA_NO_DEBUG)
    endif()
endfunction()
