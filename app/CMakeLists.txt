cmake_minimum_required(VERSION 3.6.0)

set(PROJECT_NAME RPG)
set(CPP_FILES_DIR src/main/cpp)

file(GLOB_RECURSE SOURCE_FILES "${CPP_FILES_DIR}/*.cpp" "${CPP_FILES_DIR}/*.c")
file(GLOB_RECURSE HEADER_FILES "${CPP_FILES_DIR}/*.h" "${CPP_FILES_DIR}/*.hpp")

add_library(native_app_glue STATIC
    ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
target_include_directories(native_app_glue PUBLIC
    ${ANDROID_NDK}/sources/android/native_app_glue)

find_library(log-lib
    log)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

add_library(${PROJECT_NAME} SHARED
    ${SOURCE_FILES})

target_include_directories(
  ${PROJECT_NAME}
  PUBLIC
  ${INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME}
    android
    native_app_glue
    ${log-lib}
    EGL
    GLESv3)