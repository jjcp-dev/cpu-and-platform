add_executable(kbza_tests 
    "test_address.cpp"
)

target_compile_features(kbza_tests PUBLIC cxx_std_20)
target_link_libraries(kbza_tests PRIVATE Catch2::Catch2WithMain)
target_link_libraries(kbza_tests PRIVATE kbza)

add_test(NAME kbza_tests COMMAND kbza_tests)
