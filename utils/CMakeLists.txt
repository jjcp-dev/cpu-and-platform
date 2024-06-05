add_library(utils)
target_compile_features(utils PRIVATE cxx_std_20)

target_sources(utils PRIVATE FILE_SET utils_modules TYPE CXX_MODULES FILES
    "src/Alignment.ixx"
    "src/Numbers.ixx"
    "src/Utils.ixx"
)

add_subdirectory("test")
