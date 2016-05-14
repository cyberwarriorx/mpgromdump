project(MpgRomDump)

enable_language(ASM)
set(MpgRomDump_SOURCES
	crt0.s
	main.c)

set(CMAKE_C_FLAGS "-O2 -Wall -m2")
set(CMAKE_EXE_LINKER_FLAGS "-nostartfiles -Wl,--script,${CMAKE_SOURCE_DIR}/src/bart.lk")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

add_definitions(-DMPGROMDUMP_VERSION=\"${MPGROMDUMP_VERSION}\")
add_definitions(-DREENTRANT_SYSCALLS_PROVIDED)
add_definitions(-DMISSING_SYSCALL_NAMES)

add_executable(${PROJECT_NAME} ${MpgRomDump_SOURCES})

target_link_libraries(${PROJECT_NAME} ${MpgRomDump_LIBRARIES} )

add_custom_command(TARGET ${PROJECT_NAME}
	POST_BUILD
	DEPENDS ${PROJECT_NAME}
	COMMAND ${CMAKE_OBJCOPY} --output-format=binary ${PROJECT_NAME}.elf ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.BIN
    COMMENT "Generating bin file" )

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.BIN DESTINATION ".")
install(FILES ${CMAKE_SOURCE_DIR}/CHANGELOG DESTINATION ".")
install(FILES ${CMAKE_SOURCE_DIR}/README.TXT DESTINATION ".")

