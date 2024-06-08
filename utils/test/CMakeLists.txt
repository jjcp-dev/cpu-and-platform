add_executable(test_utils
    "test_align.cpp"
    "test_is_aligned.cpp"
    "test_is_power_of_two.cpp"
    "test_address.cpp"
)

target_compile_features(test_utils PRIVATE cxx_std_20)
target_link_libraries(test_utils 
    PRIVATE 
        utils
        Catch2::Catch2WithMain
)

catch_discover_tests(test_utils)

test_build_failure(
    TARGET
        test_utils_address
    NAME
        "Utils.Address"
    SOURCES
        "build_address.cpp"
    FEATURES
        cxx_std_20
    LIBRARIES
        utils
    CASES
        ALIGNMENT_EQ_0   
            "Alignment must be a power of two"

        ALIGNMENT_POT    
            "Alignment must be a power of two"

        COPY_CTOR_UNDER_ALIGNED
            "Expected greater or equal alignment for copy-ctor"

        COPY_ASSIGNMENT_UNDER_ALIGNED
            "Expected greater or equal alignment for copy-assignment"
)
