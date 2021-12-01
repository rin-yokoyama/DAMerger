set(LIB_NAME core)
set(LIB_SOURCES
	source/RemainTime.cpp
	source/YamlParameter.cpp
	source/YamlReader.cpp
)

include_directories(include)
add_library(${LIB_NAME} SHARED ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES})

install(TARGETS ${LIB_NAME}
		LIBRARY DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)