add_executable(test_cpu 
    "test_instruction.cpp"
    "test_register_id.cpp" 
    "test_core.cpp"
)

target_compile_features(test_cpu PUBLIC cxx_std_20)
target_link_libraries(test_cpu PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_cpu PRIVATE cpu)
catch_discover_tests(test_cpu)

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
