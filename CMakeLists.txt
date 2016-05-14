CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

include(CMakeForceCompiler)
include(ExternalProject)

SET(CMAKE_SYSTEM_NAME SegaSaturn)

if (WIN32)
	set(SH_ELF_PATHS 
		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\KPIT\\GNUSH v12.02-ELF;Path]/sh-elf/bin"
		"[HKEY_LOCAL_MACHINE\\SOFTWARE\\KPIT Cummins\\GNUSH v10.02-ELF;Path]/sh-elf/bin")
else (WIN32)	        
	set(SH_ELF_PATHS "")
endif (WIN32)

find_program(SH_ELF_GCC
	NAMES sh-elf-gcc
	PATHS
		${SH_ELF_PATHS})

find_program(SH_ELF_GPP
	NAMES sh-elf-g++
	PATHS
		${SH_ELF_PATHS})
		
# Specify the cross compiler.
CMAKE_FORCE_C_COMPILER(${SH_ELF_GCC} GNU)
CMAKE_FORCE_CXX_COMPILER(${SH_ELF_GPP} GNU)
SET(CMAKE_FIND_ROOT_PATH /usr/local/share/sh-elf/bin)

find_path(IAPETUS_INCLUDE_DIR 
          NAMES iapetus.h
          PATHS ${IAPETUS_ROOT_PATH}/include
                $ENV{ProgramFiles}/iapetus/include )

if (IAPETUS_INCLUDE_DIR STREQUAL "IAPETUS_INCLUDE_DIR-NOTFOUND")
   ExternalProject_Add(iapetus
      GIT_REPOSITORY "https://github.com/cyberwarriorx/iapetus.git"
      LOG_DOWNLOAD 1
      LOG_CONFIGURE 1
      LOG_BUILD 1
      INSTALL_COMMAND "" 
   )

   ExternalProject_Get_Property(iapetus source_dir)
   set(IAPETUS_INCLUDE_DIR ${source_dir}/src)
endif(IAPETUS_INCLUDE_DIR STREQUAL "IAPETUS_INCLUDE_DIR-NOTFOUND")

PROJECT(MpgRomDump)

include_directories(${IAPETUS_INCLUDE_DIR})

#CONFIGURE_FILE(config.h.cmake config.h)

set(MPGROMDUMP_VERSION_MAJOR 1)
set(MPGROMDUMP_VERSION_MINOR 0)
set(MPGROMDUMP_VERSION_PATCH 0)
set(MPGROMDUMP_VERSION "${MPGROMDUMP_VERSION_MAJOR}.${MPGROMDUMP_VERSION_MINOR}${MPGROMDUMP_VERSION_PATCH}")

set(CPACK_SOURCE_GENERATOR TGZ)
set(CPACK_PACKAGE_VERSION_MAJOR ${MPGROMDUMP_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MPGROMDUMP_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MPGROMDUMP_VERSION_PATCH})
set(CPACK_PACKAGE_VENDOR "Cyber Warrior X")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/COPYING")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "$MPGROMDUMP-${MPGROMDUMP_VERSION}")
set(CPACK_PACKAGE_FILE_NAME "MPGROMDUMP-${MPGROMDUMP_VERSION}")
include(CPack)

set(CMAKE_CONFIGURATION_TYPES Release)

find_library(IAPETUS_LIB
             NAMES iapetus
             PATHS ${IAPETUS_ROOT_PATH}/lib
                   $ENV{ProgramFiles}/iapetus/lib)

if (IAPETUS_LIB STREQUAL "IAPETUS_LIB-NOTFOUND")
   ExternalProject_Get_Property(iapetus binary_dir)
   #add_dependencies(${PROJECT_NAME} iapetus)
   set(IAPETUS_LIB "${binary_dir}/src/${CMAKE_FIND_LIBRARY_PREFIXES}iapetus.a")
endif(IAPETUS_LIB STREQUAL "IAPETUS_LIB-NOTFOUND")

set(MpgRomDump_LIBRARIES ${IAPETUS_LIB})

add_subdirectory(src)