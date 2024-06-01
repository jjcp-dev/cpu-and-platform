
function (BUILD_FAILURE_TEST)

    cmake_parse_arguments(
        ARG 
        "" 
        "NAME" 
        "SOURCES;FEATURES;LIBRARIES;DEFINES" 
        ${ARGN}
    )

    foreach(opt IN LISTS ARG_DEFINES)

		add_executable(${ARG_NAME}_${opt} ${ARG_SOURCES})

		target_compile_features(${ARG_NAME}_${opt} PRIVATE ${ARG_FEATURES})

		target_link_libraries(${ARG_NAME}_${opt} PRIVATE ${ARG_LIBRARIES})

        target_compile_definitions(${ARG_NAME}_${opt} PRIVATE ${opt})

        set_target_properties(${ARG_NAME}_${opt} PROPERTIES 
            EXCLUDE_FROM_ALL TRUE
            EXCLUDE_FROM_DEFAULT_BUILD TRUE
        )

        add_test(NAME ${ARG_NAME}.${opt}
                 COMMAND ${CMAKE_COMMAND} --build . --target ${ARG_NAME}_${opt} --config $<CONFIGURATION>
                 WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

        set_tests_properties(${ARG_NAME}.${opt} PROPERTIES WILL_FAIL TRUE)

    endforeach()

endfunction()