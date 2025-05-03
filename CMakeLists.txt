cmake_minimum_required(VERSION 3.20.0)
cmake_policy(SET CMP0054 NEW)

set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE)
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb -O0 -fno-exceptions")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -fno-exceptions")
add_compile_definitions()

project(robcmp)

set(CMAKE_CXX_STANDARD 17)

message(STATUS "CC Compiler used: ${CC}")

find_package(LLVM REQUIRED CONFIG)
find_package(FLEX 2.6 REQUIRED)
find_package(BISON 3.8 REQUIRED)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS} ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

file(GLOB robcmp_SRC CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/**/*.cpp"
)

flex_target(lexer "${CMAKE_CURRENT_SOURCE_DIR}/src/Language.l" "${CMAKE_BINARY_DIR}/Language_l.cpp")

bison_target(scanner_main 
    "${CMAKE_BINARY_DIR}/Language_gen.y"
    "${CMAKE_BINARY_DIR}/Language_gen.cpp"
    DEFINES_FILE "${CMAKE_BINARY_DIR}/Language_gen_y.hpp"
    COMPILE_FLAGS "-Wall -Wno-deprecated")
bison_target(scanner_use
    "${CMAKE_BINARY_DIR}/LanguageUse_gen.y"
    "${CMAKE_BINARY_DIR}/LanguageUse_gen.cpp"
    COMPILE_FLAGS "-Wall -Wno-deprecated")

# Language_gen.y
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/Language_gen.y
        COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageHeader.y ${CMAKE_CURRENT_SOURCE_DIR}/src/Language.y > ${CMAKE_BINARY_DIR}/Language_gen.y
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageHeader.y ${CMAKE_CURRENT_SOURCE_DIR}/src/Language.y
)
# LanguageUse_gen.y
add_custom_command(
        OUTPUT ${CMAKE_BINARY_DIR}/LanguageUse_gen.y
        COMMAND cat ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageHeader.y ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageUse.y > ${CMAKE_BINARY_DIR}/LanguageUse_gen.y
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageHeader.y ${CMAKE_CURRENT_SOURCE_DIR}/src/LanguageUse.y
)
add_custom_target(parsers
        DEPENDS ${CMAKE_BINARY_DIR}/Language_gen.y ${CMAKE_BINARY_DIR}/LanguageUse_gen.y)

add_executable(robcmp
	${FLEX_lexer_OUTPUTS}
	${BISON_scanner_main_OUTPUTS} ${BISON_scanner_use_OUTPUTS}
	${robcmp_SRC})

add_flex_bison_dependency(lexer scanner_main)
add_flex_bison_dependency(lexer scanner_use)
add_dependencies(robcmp parsers)

find_library(LLVM_MONOLITHIC_LIBRARY LLVM HINTS ${LLVM_LIBRARY_DIRS})

if (LLVM_MONOLITHIC_LIBRARY)
	message(STATUS "LLVM is using monolithic libLLVM.so")
	target_link_libraries(robcmp LLVM)
else()
	llvm_map_components_to_libnames(llvm_libs support core irreader passes
    		armasmparser armcodegen 
    		avrasmparser avrcodegen 
    		x86asmparser x86codegen)

	target_link_libraries(robcmp ${llvm_libs})
endif()

set_target_properties(robcmp PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
    VS_DEBUGGER_COMMAND_ARGUMENTS "-a atmega328p -Oz ../platformio/samples/atmega328p-blink/src/main.rob")
