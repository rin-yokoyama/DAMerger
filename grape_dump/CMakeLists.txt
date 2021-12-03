include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/idaq2root/include)
include_directories(${GRETINA_DECODER_DIR}/cmake/inc/inc)

set(EXE_NAME grape_dump)
set(LIB_NAME GrapeData)

ROOT_GENERATE_DICTIONARY(G__GrapeData GrapeData.hpp GrapeDataDumpSelector.hpp LINKDEF include/GrapeDataLinkDef.hpp)

add_library(${LIB_NAME} SHARED source/GrapeDataDumpSelector.cpp G__GrapeData.cxx)
target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES} HiCARI)

add_executable(${EXE_NAME} source/GrapeDataDumpMain.cpp)
target_link_libraries(${EXE_NAME} ${ROOT_LIBRARIES} ${LIB_NAME} HiCARI)

install(TARGETS ${EXE_NAME}
		RUNTIME DESTINATION bin
		)
install(TARGETS ${LIB_NAME}
		LIBRARY DESTINATION lib
		)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libGrapeData_rdict.pcm
		DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)