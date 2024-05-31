add_executable(kbza_tests 
    "test_address.cpp"
    "test_instruction.cpp"
    "test_register_id.cpp")

target_compile_features(kbza_tests PUBLIC cxx_std_20)
target_link_libraries(kbza_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(kbza_tests PRIVATE kbza)

add_test(NAME kbza_tests COMMAND kbza_tests)

build_failure_test(
    NAME
        kbza_test_address
    SOURCES
        "test_address_bf.cpp"
    FEATURES
        cxx_std_20
    LIBRARIES
        kbza
    DEFINES
        ALIGNMENT_EQ_0
        ALIGNMENT_POT
        COPY_CTOR_UNDER_ALIGNED
        COPY_ASSIGNMENT_UNDER_ALIGNED
)
