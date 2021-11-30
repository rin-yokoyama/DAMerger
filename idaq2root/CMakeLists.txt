set(EXE_NAME idaq2root)
include_directories(include)
ROOT_GENERATE_DICTIONARY(G__IDaqData include/IDaqData.hpp LINKDEF include/IDaqDataLinkDef.hpp)
add_executable(${EXE_NAME} source/idaq2root_main.cpp G__IDaqData.cxx)
target_link_libraries(${EXE_NAME} ${ROOT_LIBRARIES} XMLParser anaroot anacore)

install(TARGETS ${EXE_NAME}
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
		)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libIDaqData_rdict.pcm
		DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)