# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
set(SFML_ROOT "${CMAKE_SOURCE_DIR}/SFML")
set(SFML_INCLUDE_DIR "${SFML_ROOT}/include")
set(SFML_LIBRARY_DIR "${SFML_ROOT}/lib")

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIBRARY_DIR})

# Add source to this project's executable.
add_executable (CMakeProject1 "CMakeProject1.cpp" "CMakeProject1.h")

# Set C++ standard to 17 for better compatibility
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD 17)
  set_property(TARGET CMakeProject1 PROPERTY CXX_STANDARD_REQUIRED ON)
endif()

# Add compiler-specific flags for MSVC
if (MSVC)
  target_compile_options(CMakeProject1 PRIVATE /Zc:__cplusplus)
  # Ensure proper C++ standard library headers are available
  target_compile_definitions(CMakeProject1 PRIVATE _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)
endif()

# Link SFML libraries (prefer dynamic libs to match provided bin/ DLLs)
if (MSVC)
  target_link_libraries(CMakeProject1 PRIVATE
    debug ${SFML_LIBRARY_DIR}/sfml-graphics-d.lib
    optimized ${SFML_LIBRARY_DIR}/sfml-graphics.lib
    debug ${SFML_LIBRARY_DIR}/sfml-window-d.lib
    optimized ${SFML_LIBRARY_DIR}/sfml-window.lib
    debug ${SFML_LIBRARY_DIR}/sfml-system-d.lib
    optimized ${SFML_LIBRARY_DIR}/sfml-system.lib
  )
else()
  target_link_libraries(CMakeProject1 PRIVATE sfml-graphics sfml-window sfml-system)
endif()

# Copy SFML DLLs next to the executable after build (Windows)
if (WIN32)
  add_custom_command(TARGET CMakeProject1 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_ROOT}/bin" "$<TARGET_FILE_DIR:CMakeProject1>")
endif()
# TODO: Add tests and install targets if needed.
