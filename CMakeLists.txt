cmake_minimum_required(VERSION 3.25)

project(test_dt)
add_executable(test_dt test_dt.c)
target_include_directories(test_dt PUBLIC build)

find_package(Git QUIET)
if(GIT_FOUND)
  execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --abbrev=12 --always
    WORKING_DIRECTORY                ${CMAKE_CURRENT_SOURCE_DIR}
    OUTPUT_VARIABLE                  BUILD_VERSION
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE                   stderr
    RESULT_VARIABLE                  return_code
  )
  if(return_code)
    message(STATUS "git describe failed: ${stderr}")
  elseif(NOT "${stderr}" STREQUAL "")
    message(STATUS "git describe warned: ${stderr}")
  else()
    message(STATUS "BUILD_VERSION: ${BUILD_VERSION}")
  endif()
endif()

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/version.h.in ${CMAKE_CURRENT_SOURCE_DIR}/build/version.h)

set(BOARD_NAME boardA)
set(DEVICETREE_GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(DEVICETREE_GENERATED_FILE ${DEVICETREE_GENERATED_DIR}/devicetree_generated.h)
set(DEVICETREE_INI ${CMAKE_CURRENT_SOURCE_DIR}/boards/boardA/devicetree.ini)
set(DEVICETREE_OVERLAY ${CMAKE_CURRENT_SOURCE_DIR}/devicetree.conf)

add_custom_command(OUTPUT ${DEVICETREE_GENERATED_FILE}
  COMMAND 
  python ${CMAKE_CURRENT_SOURCE_DIR}/gendefine.py 
  ${DEVICETREE_GENERATED_DIR} 
  ${DEVICETREE_INI} 
  ${DEVICETREE_OVERLAY}

  DEPENDS ${DEVICETREE_INI} ${DEVICETREE_OVERLAY}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "GEN DEVICETREE"
  )

target_sources(test_dt PUBLIC ${DEVICETREE_GENERATED_FILE})

# add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
#   PRE_BUILD
#   COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/gendefine.py ${DEVICETREE_GENERATED_DIR} ${DEVICETREE_INI} ${DEVICETREE_OVERLAY}
#   COMMENT "GEN DEVICETREE"
#   )