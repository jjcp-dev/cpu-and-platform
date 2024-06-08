add_executable(test_platform 
    "test_memory_controller.cpp"
)

target_compile_features(test_platform PUBLIC cxx_std_20)
target_link_libraries(test_platform PRIVATE Catch2::Catch2WithMain)
target_link_libraries(test_platform PRIVATE platform utils)

catch_discover_tests(test_platform)
