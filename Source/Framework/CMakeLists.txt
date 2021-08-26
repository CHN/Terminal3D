project(Framework)

CreateTarget(${PROJECT_NAME} EXECUTABLE)

target_link_libraries(${PROJECT_NAME} PRIVATE Config Engine)