add_executable(test_platform 
    "test_address.cpp"
    "test_memory_controller.cpp"
)

target_compile_features(test_platform PUBLIC cxx_std_20)
target_link_libraries(test_platform PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_platform PRIVATE platform)
catch_discover_tests(test_platform)

build_failure_test(
    TARGET
        "test_platform_address"
    NAME
        "Platform::Address"
    SOURCES
        "build_address.cpp"
    FEATURES
        cxx_std_20
    LIBRARIES
        platform
    DEFINES
        ALIGNMENT_EQ_0
        ALIGNMENT_POT
        COPY_CTOR_UNDER_ALIGNED
        COPY_ASSIGNMENT_UNDER_ALIGNED
)
