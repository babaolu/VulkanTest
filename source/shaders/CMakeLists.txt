cmake_minimum_required(VERSION 3.20)

project(ShaderCompiler)

# Find glslangValidator
find_program(GLSLANG_VALIDATOR glslangValidator)
if (NOT GLSLANG_VALIDATOR)
    message(FATAL_ERROR "glslangValidator not found. Make sure it is installed and in your PATH.")
endif()

# Directories
set(SHADER_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(SPIRV_DIR ${CMAKE_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${SPIRV_DIR})  # Ensure the output directory exists

# Function to compile shaders
function(compile_shader source_file output_file)
    add_custom_command(
        OUTPUT ${output_file}
        COMMAND ${GLSLANG_VALIDATOR} -V ${source_file} -o ${output_file}
        DEPENDS ${source_file}
        COMMENT "Compiling GLSL shader ${source_file} to SPIR-V"
    )
endfunction()

# Shaders
set(VERTEX_SHADER ${SHADER_DIR}/shader.vert)
set(FRAGMENT_SHADER ${SHADER_DIR}/shader.frag)

set(VERTEX_SPV ${SPIRV_DIR}/shader.vert.spv)
set(FRAGMENT_SPV ${SPIRV_DIR}/shader.frag.spv)

compile_shader(${VERTEX_SHADER} ${VERTEX_SPV})
compile_shader(${FRAGMENT_SHADER} ${FRAGMENT_SPV})

# Define a custom target to build all shaders
add_custom_target(ShaderTargets DEPENDS ${VERTEX_SPV} ${FRAGMENT_SPV})
