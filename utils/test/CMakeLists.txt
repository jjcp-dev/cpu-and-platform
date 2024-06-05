add_executable(test_utils
    "test_align.cpp"
    "test_is_aligned.cpp"
    "test_is_power_of_two.cpp"
)

target_compile_features(test_utils PRIVATE cxx_std_20)
target_link_libraries(test_utils 
    PRIVATE 
        utils
        Catch2::Catch2WithMain
)

catch_discover_tests(test_utils)

# build_failure_test(
#     NAME
#         "Kbza-fail-build.Address"
#     SOURCES
#         "test_address_bf.cpp"
#     FEATURES
#         cxx_std_20
#     LIBRARIES
#         kbza
#     DEFINES
#         ALIGNMENT_EQ_0
#         ALIGNMENT_POT
#         COPY_CTOR_UNDER_ALIGNED
#         COPY_ASSIGNMENT_UNDER_ALIGNED
# )
