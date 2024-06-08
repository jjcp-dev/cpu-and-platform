add_library(platform)

target_sources(platform PRIVATE FILE_SET platform_modules TYPE CXX_MODULES FILES
    "src/Platform.ixx" 
    "src/MemoryController.ixx" 
    
)

target_compile_features(platform PRIVATE cxx_std_20)
target_link_libraries(platform PRIVATE utils)

add_subdirectory("test")
