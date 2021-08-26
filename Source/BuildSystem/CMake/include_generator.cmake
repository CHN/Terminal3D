macro(GenerateIncludes [PROJECT_NAME])

	set(SOURCE_DIR ${PROJECT_SOURCE_DIR})
	set(LIB_NAME ${PROJECT_NAME})

	file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp")
	file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

	list(LENGTH SOURCES SOURCES_COUNT)

	if(${SOURCES_COUNT} EQUAL 0)
		message("${name} library is not generated due to having 0 sources")
		return()
	endif()

	add_library(${LIB_NAME} STATIC ${HEADERS} ${SOURCES})

	set(PUBLIC_HEADER_PATHS "")

	foreach(HEADER_PATH IN LISTS HEADERS)
	
		if(HEADER_PATH MATCHES "Public")
	
			get_filename_component(PATH_DIRECTORY ${HEADER_PATH} PATH)
			message(${PATH_DIRECTORY})
			list(APPEND PUBLIC_HEADER_PATHS ${PATH_DIRECTORY})

		endif()

	endforeach()

	target_include_directories(${LIB_NAME} PUBLIC ${PUBLIC_HEADER_PATHS} ${SOURCE_DIR})

	set_target_properties(${LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

	source_group(TREE ${SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

endmacro()