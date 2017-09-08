cmake_minimum_required ( VERSION 3.8 )
project (bsglrender CXX)

#file(MAKE_DIRECTORY "${PROJECT_SOURCE_DIR}/data")

SET (TOP "${PROJECT_SOURCE_DIR}/..")
SET (SRC_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SHADERS_DIR "${SRC_DIR}/shaders")

SET (SCRATCH "${TOP}/../..")
SET (GLM_DIR "${SCRATCH}/glm-0.9.7.6/glm" CACHE PATH "" )

SET (INCLUDE_DIRS ${SRC_DIR})

SET (GLFW_INCLUDE_DIR "" CACHE PATH "" )
SET (GLFW_LIB_DIR "" CACHE PATH "" )
SET (GLES_INCLUDE_DIR "" CACHE PATH "" )
SET (GLES_LIB_DIR "" CACHE PATH "" )
SET (GLEW_INCLUDE_DIR "" CACHE PATH "" )
SET (GLEW_LIB_DIR "" CACHE PATH "" )

FILE (GLOB SRC_FILES
    ${SRC_DIR}/*.cpp
    ${SRC_DIR}/*.h
	${SHADERS_DIR}/*
	)

SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

include_directories( ${SRC_DIR}
                     ${GLM_DIR}
                     ${GLFW_INCLUDE_DIR}
                     ${GLEW_INCLUDE_DIR}
                     ${GLES_INCLUDE_DIR} )

link_directories( ${GLFW_LIB_DIR}
                  ${GLEW_LIB_DIR}
                  ${GLES_LIB_DIR} )

add_executable(bsglrender WIN32 ${SRC_FILES})

set_target_properties(bsglrender PROPERTIES LINKER_LANGUAGE CXX)

target_link_libraries(bsglrender "glew32" "glfw3" "opengl32" "libGLESv2")

add_custom_command(
        TARGET bsglrender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${SRC_DIR}/shaders
                $<TARGET_FILE_DIR:bsglrender>/shaders)
				
add_custom_command(
        TARGET bsglrender POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${SRC_DIR}/shaders
                ${CMAKE_CURRENT_BINARY_DIR}/shaders)

IF(WIN32) # Check if we are on Windows
    set_target_properties(bsglrender PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:CONSOLE")
    set_target_properties(bsglrender PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
	
	set_target_properties(bsglrender PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/Debug")
ENDIF()
