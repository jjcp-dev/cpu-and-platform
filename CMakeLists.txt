cmake_minimum_required (VERSION 3.28)

project ("cpu_and_platform")

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

add_subdirectory(lib/Catch2)

include(CTest)
include(Catch)
include(cmake/BuildFailureTest.cmake)

add_subdirectory(utils)
add_subdirectory(cpu)
add_subdirectory(platform)

# add_executable(os "main.cpp")
# target_link_libraries(os PRIVATE kbza)
# target_compile_features(os PRIVATE cxx_std_20)
