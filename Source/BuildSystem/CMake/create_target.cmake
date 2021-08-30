include("set_platform_dependent_directories")

function(CreateTarget PROJECT_NAME PROJECT_TYPE)

	set(NAME ${PROJECT_NAME})
	set(SOURCE_DIR ${PROJECT_SOURCE_DIR})

	file(GLOB_RECURSE HEADERS "${SOURCE_DIR}/*.h" "${SOURCE_DIR}/*.hpp")
	file(GLOB_RECURSE SOURCES "${SOURCE_DIR}/*.cpp")

	list(LENGTH HEADERS HEADER_COUNT)
	list(LENGTH SOURCES SOURCE_COUNT)

	set(PUBLIC_HEADER_PATHS "")

	foreach(HEADER_PATH IN LISTS HEADERS)
	
		if(HEADER_PATH MATCHES "Public")
	
			get_filename_component(PATH_DIRECTORY ${HEADER_PATH} PATH)
			list(APPEND PUBLIC_HEADER_PATHS ${PATH_DIRECTORY})

		endif()

	endforeach()

	set(PLATFORM_DEPENDENT_DIR "PlatformDependent")

	SetPlatformDependentDirectories(HEADERS)
	SetPlatformDependentDirectories(SOURCES)
	
	if(${SOURCE_COUNT} EQUAL 0 AND ${HEADER_COUNT} EQUAL 0)
		message("\"${PROJECT_NAME}\" library is not generated due to having 0 headers and sources")
		return()
	endif()

	if(PROJECT_TYPE MATCHES LIBRARY)

		if(${SOURCE_COUNT} GREATER 0)

			add_library(${NAME} STATIC ${HEADERS} ${SOURCES})
			target_include_directories(${NAME} PUBLIC ${PUBLIC_HEADER_PATHS} ${SOURCE_DIR})
			set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)

		else()

			add_library(${NAME} INTERFACE)
			target_include_directories(${NAME} INTERFACE ${PUBLIC_HEADER_PATHS})

		endif()

	elseif(PROJECT_TYPE MATCHES EXECUTABLE)

		add_executable(${NAME} ${HEADERS} ${SOURCES})

	endif()

	source_group(TREE ${SOURCE_DIR} FILES ${HEADERS} ${SOURCES})

endfunction()