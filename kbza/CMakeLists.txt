add_library(kbza)
target_compile_features(kbza PUBLIC cxx_std_20)

target_sources(kbza PUBLIC FILE_SET kbza_modules TYPE CXX_MODULES FILES
 "Kbza.ixx"
 "Utils.ixx"
 "Address.ixx"
 "Opcode.ixx"
)

 add_subdirectory(tests)
