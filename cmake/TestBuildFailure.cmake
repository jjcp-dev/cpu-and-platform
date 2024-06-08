function (TEST_BUILD_FAILURE)

    cmake_parse_arguments(
        ARG 
        "" 
        "TARGET;NAME" 
        "SOURCES;FEATURES;LIBRARIES;CASES" 
        ${ARGN}
    )

	while(NOT "${ARG_CASES}" STREQUAL "")

		list(POP_FRONT ARG_CASES DEFINE)
		list(POP_FRONT ARG_CASES MATCH)

		add_executable(${ARG_TARGET}_${DEFINE} ${ARG_SOURCES})
		target_compile_features(${ARG_TARGET}_${DEFINE} PRIVATE ${ARG_FEATURES})
		target_link_libraries(${ARG_TARGET}_${DEFINE} PRIVATE ${ARG_LIBRARIES})
		target_compile_definitions(${ARG_TARGET}_${DEFINE} PRIVATE ${DEFINE})
		set_target_properties(${ARG_TARGET}_${DEFINE} PROPERTIES 
			EXCLUDE_FROM_ALL TRUE
			EXCLUDE_FROM_DEFAULT_BUILD TRUE
		)

		add_test(
			NAME 
				"${ARG_NAME}.${DEFINE}"
			COMMAND 
				${CMAKE_COMMAND} --build . 
								 --target ${ARG_TARGET}_${DEFINE} 
								 --config $<CONFIGURATION>
			WORKING_DIRECTORY 
				${CMAKE_BINARY_DIR}
		)

		set_tests_properties("${ARG_NAME}.${DEFINE}" 
			PROPERTIES 
				# WILL_FAIL 
				# 	TRUE
				PASS_REGULAR_EXPRESSION 
					${MATCH}
		)

	endwhile()

endfunction()