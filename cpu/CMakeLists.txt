add_library(cpu)

target_sources(cpu PRIVATE FILE_SET cpu_modules TYPE CXX_MODULES FILES
    "src/Cpu.ixx"
    "src/Opcode.ixx"
    "src/RegisterId.ixx"
    "src/Instruction.ixx"
    
    "src/Status.ixx"
    "src/Core.ixx"
    "src/Core.cpp"
    "src/InterruptId.ixx" 
)

target_compile_features(cpu PRIVATE cxx_std_20)
target_link_libraries(cpu PRIVATE utils platform)

add_subdirectory("test")
