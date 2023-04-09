cmake_minimum_required (VERSION 3.8)

set(VITIS_DIR D:/app/Xilinx/Vitis/2022.2)

set(CMAKE_TRY_COMPILE_TARGET_TYPE "STATIC_LIBRARY")

set(CROSS_COMPILE aarch64-none-elf-)
set(TOOLCHAIN_HOME ${VITIS_DIR}/gnu/aarch64/nt/aarch64-none/bin)
find_program(CMAKE_C_COMPILER ${CROSS_COMPILE}gcc   PATHS ${TOOLCHAIN_HOME} NO_DEFAULT_PATH)
find_program(CMAKE_CXX_COMPILER ${CROSS_COMPILE}g++   PATHS ${TOOLCHAIN_HOME} NO_DEFAULT_PATH)

find_program(XILINX_CACULATE_ELF_SIZE ${CROSS_COMPILE}size   PATHS ${TOOLCHAIN_HOME} NO_DEFAULT_PATH)

project(test_cmake)
add_executable(test_cmake src/app.c)


# add_definitions(-D__hal__ -DALT_NO_INSTRUCTION_EMULATION -D__ucosii__)
set(PLATFORM_NAME ucos_platform)

set(BSP_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ucos_platform/psu_cortexa53_0/ucos_domain/bsp)
set(SW_DOMAIN_DIR ${BSP_DIR}/psu_cortexa53_0)
set(BSP_INCLUDE_DIR ${SW_DOMAIN_DIR}/include)
set(BSP_LIB_DIR ${SW_DOMAIN_DIR}/lib)

# set(SW_DOMAIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../ucos_platform/export/ucos_platform/sw/ucos_platform/ucos_domain)
# target_include_directories(test_cmake PUBLIC ${SW_DOMAIN_DIR}/bspinclude/include)
target_include_directories(test_cmake PUBLIC ${BSP_INCLUDE_DIR})


set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_CXX_FLAGS_INIT "")
set(CMAKE_EXE_LINKER_FLAGS "")
set(CMAKE_CXX_STANDARD_LIBRARIES "")
set(CMAKE_EXECUTABLE_SUFFIX .elf)

set(TOOLCHAIN_LD_FLAGS "")
set(TOOLCHAIN_C_FLAGS "")

list(APPEND TOOLCHAIN_C_FLAGS  -Wall -fmessage-length=0 -MMD -MP)

target_compile_options(${CMAKE_PROJECT_NAME} PUBLIC ${TOOLCHAIN_C_FLAGS})


list(APPEND TOOLCHAIN_LD_FLAGS   -Wl,-T -Wl,${CMAKE_CURRENT_SOURCE_DIR}/src/lscript.ld)
# list(APPEND TOOLCHAIN_LD_FLAGS   -L${SW_DOMAIN_DIR}/bsplib/lib)
list(APPEND TOOLCHAIN_LD_FLAGS   -L${BSP_LIB_DIR})
list(APPEND TOOLCHAIN_LD_FLAGS   -Wl,--start-group,-lucos,-lgcc,-lc,--end-group -Wl,--start-group,-lucos,-lxil,-lgcc,-lc,--end-group)

target_link_options(${CMAKE_PROJECT_NAME} PUBLIC ${TOOLCHAIN_LD_FLAGS})

set(CMAKE_CXX_LINK_EXECUTABLE
"<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS>  <OBJECTS> -o <TARGET> <LINK_FLAGS>")

set(CMAKE_C_LINK_EXECUTABLE
"<CMAKE_CXX_COMPILER> <FLAGS> <CMAKE_CXX_LINK_FLAGS>  <OBJECTS> -o <TARGET> <LINK_FLAGS>")

# add_custom_command(TARGET ${CMAKE_PROJECT_NAME}
#   POST_BUILD
#   COMMAND ${XILINX_CACULATE_ELF_SIZE} ${CMAKE_PROJECT_NAME}${CMAKE_EXECUTABLE_SUFFIX}
#   COMMENT "XILINX_CACULATE_ELF_SIZE"
#   )

# set(XLNX_MAKE ${VITIS_DIR}/gnuwin/bin/make.exe)
# D:\app\Xilinx\Vitis\2022.2\gnuwin\bin\make.exe

# execute_process(  
#   COMMAND 
#   ${XLNX_MAKE} all
#   WORKING_DIRECTORY ${BSP_DIR}
# )