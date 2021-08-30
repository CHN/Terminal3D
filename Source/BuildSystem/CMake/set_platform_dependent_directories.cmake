function(SetPlatformDependentDirectories SOURCE_FILES)
	
	set(PLATFORM_DEPENDENT_DIR "PlatformDependent")
	
	foreach(PLATFORM IN LISTS PLATFORMS)
		
		if(PLATFORM MATCHES ${CURRENT_PLATFORM})
			
			continue()
		
		endif()

		foreach(SOURCE_PATH IN LISTS ${SOURCE_FILES})

			if(SOURCE_PATH MATCHES ${PLATFORM_DEPENDENT_DIR})

				if(SOURCE_PATH MATCHES ${PLATFORM})

					list(REMOVE_ITEM ${SOURCE_FILES} ${SOURCE_PATH})

				endif()
			
			endif()

		endforeach()

	endforeach()

	set(${SOURCE_FILES} ${${SOURCE_FILES}} PARENT_SCOPE)

endfunction()