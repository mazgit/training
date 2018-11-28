## Required Settings  #########################################
cmake_minimum_required(VERSION 3.5)
project(example)
###############################################################

## Misc Settings #########################################
#enable make verbos
set(CMAKE_VERBOSE_MAKEFILE ON)
###########################################################

## Outout Locations ########################################
#Static Libs
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/arch)
link_directories(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
#Dynamic Libs
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#Binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
############################################################

## Misc Settings #########################################
#set LSP project path
set(LSP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/project_cfg/lsp/default")
message(STATUS "${PROJECT_NAME} LSP PATH: ${LSP_PATH}")

## subdirectories for build
set(MBIN_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mbin/${PROJECT_NAME}")
set(MBIN_OUTPUT_OBJECT "${PROJECT_NAME}")
set(LSP_BUILD_DIRECTORY "${MBIN_DIRECTORY}/lsp")


## COMPILER FLAGS #######################################################################
#set compiler flags
set_source_files_properties(${ASIC_O0_SOURCES}
  PROPERTIES
  COMPILE_FLAGS "-keep -O0"
  )

set_source_files_properties(${ASIC_OS_SOURCES}
  PROPERTIES
  COMPILE_FLAGS "-keep -Os"
  )

#compile options
set(ENABLE_GDB_DEBUG TRUE)  #enable gdb debug options
set(REMOVE_DEAD_CODE FALSE) #enable linker to remove dead code

#initializations
set(DEAD_CODE_EXTRACT "")
set(GDB_DEBUG "")

if(${ENABLE_GDB_DEBUG})
  set(GDB_DEBUG "-g")
endif()

if(${REMOVE_DEAD_CODE})
  set(DEAD_CODE_EXTRACT "-ffunction-sections -fdata-sections -Wl,--gc-sections")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GDB_DEBUG} ${DEAD_CODE_EXTRACT} -fsigned-char -Wall -Werror")

set(ASIC_SOURCES
  src/example.c
  src/blah1.c
  src/blah2.c
  )

## LANGUAGE EXTENSIONS  #################################################################
#enables ASM language support for *.S files
enable_language(ASM)

#set assembler flags
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}")

## BUILD ################################################################################
#main binary build for core.
add_executable(${PROJECT_NAME}  ${ASIC_SOURCES})

set(ALL_CMDS "")

message(STATUS "${ASIC_SOURCES}")

#run through each name and generate new command to run
foreach(SOURCE_NAME ${ASIC_SOURCES})

  #preprocess target name 
  string(REGEX REPLACE "[./\-]" "_" SOURCE_NAME_PP ${SOURCE_NAME})
  ##string(REGEX REPLACE "\\.c$" ".pp" SOURCE_NAME_PP ${SOURCE_NAME})
  
  set(ALL_CMDS "${ALL_CMDS} ${PROJECT_NAME}_post_process_${SOURCE_NAME_PP}")
  ##set(ALL_CMDS "${ALL_CMDS} ${SOURCE_NAME}")

  ##set(ALL_CMDS "${ALL_CMDS} ${SOURCE_NAME_PP}")

  ##message(STATUS "Generating: ${SOURCE_NAME} -> ${SOURCE_NAME_PP}")
  
  ##add_custom_command(OUTPUT ${SOURCE_NAME_PP}
  ##  COMMAND echo "Processing ${SOURCE_NAME}"
  ##  COMMAND touch ${SOURCE_NAME_PP}
  ##  COMMENT "Process: ${SOURCE_NAME}"
  ##  )

  add_custom_target(${PROJECT_NAME}_post_process_${SOURCE_NAME_PP}
    COMMAND echo "Processing ${SOURCE_NAME}"
    COMMENT "Process: ${SOURCE_NAME}"
    )

  ##set(ALL_CMDS "${ALL_CMDS} && echo ${SOURCE_NAME} ")
endforeach()

add_custom_target(${PROJECT_NAME}_run_all_commands
  #COMMAND ${ALL_CMDS}
  #COMMAND echo bin/test
  DEPENDS ${ALL_CMDS}
  COMMENT "RUN ALL COMMANDS"
  )


add_custom_target(testing
  COMMAND echo "test1" && echo "test2"
  COMMENT "Process: ${SOURCE_NAME}"
  )

message(STATUS "DONE")
