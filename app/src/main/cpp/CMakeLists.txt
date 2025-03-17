cmake_minimum_required(VERSION 3.14.7 FATAL_ERROR)
cmake_policy(VERSION 3.14.7...3.28.1)

set(PROJECT_NAME RPG)
project(${PROJECT_NAME})

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CPP_DIR app/src/main/cpp)

# Execute the script to download and extract SDL3 and SDL3_image
execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/download_vendors.sh
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                RESULT_VARIABLE DOWNLOAD_RESULT)

# Check if the script executed successfully
if (NOT DOWNLOAD_RESULT EQUAL 0)
  message(FATAL_ERROR "Failed to download SDL3 and SDL3_image.")
endif()

# This assumes the SDL source is available in vendor/SDL
add_subdirectory(vendor/SDL3 EXCLUDE_FROM_ALL)
add_subdirectory(vendor/SDL3_image EXCLUDE_FROM_ALL)

# Enable shared libraries
set(BUILD_SHARED_LIBS ON)
set(SDL3_DISABLE_UNINSTALL ON CACHE BOOL "" FORCE)
set(SDL_TEST_ENABLED_BY_DEFAULT OFF)

# Disable Things
if (ANDROID)
  set(SDL3_DISABLE_SDL3MAIN ON CACHE BOOL "" FORCE)
  set(SDL3_BUILD_TESTS OFF CACHE BOOL "Disable SDL3 tests" FORCE)
  set(SDL3_BUILD_SHARED_LIBS ON CACHE BOOL "Enable shared libraries" FORCE)
  set(SDL3_USE_COREVIDEO OFF CACHE BOOL "Disable CoreVideo (macOS)" FORCE)
  set(SDL3_USE_OPENGL OFF CACHE BOOL "Disable OpenGL" FORCE)
  set(SDL3_USE_X11 OFF CACHE BOOL "Disable X11" FORCE)
  set(SDL3_USE_WINDOWS OFF CACHE BOOL "Disable Windows specific code" FORCE)
endif()

# Android-specific setup
if (ANDROID)
  file(REMOVE_RECURSE ${CMAKE_SOURCE_DIR}/../assets/res)
  file(COPY ${CMAKE_SOURCE_DIR}/res DESTINATION ${CMAKE_SOURCE_DIR}/../assets)
endif()

# Find all .cpp and .h files
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.c")
file(GLOB_RECURSE HEADER_FILES "*.h" "*.hpp")

# Add header file directories to include path
foreach (_headerFile ${HEADER_FILES})
  get_filename_component(_dir ${_headerFile} PATH)
  list(APPEND INCLUDE_DIRS ${_dir})
endforeach()

include_directories(${INCLUDE_DIRS})

# Create executable/library based on platform
if (ANDROID)
  add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
else()
  add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 SDL3_image::SDL3_image)