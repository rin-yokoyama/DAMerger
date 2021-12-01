#ROOT_GENERATE_DICTIONARY(G__TSScanData include/OutputTreeData.hpp LINKDEF include/TSScanDataLinkDef.h)
set(LIB_NAME TSScan)
set(LIB_SOURCES
	source/IDaqMyriadTSScanner.cpp
	source/IDaqLUPOTSScanner.cpp
	source/CompassTSScanner.cpp
#	G__TSScanData.cxx
)
set(COMPASS_EXE compass_ts_merger)
add_executable(${COMPASS_EXE} source/CompassTSMergerMain.cpp)

include_directories(include)
include_directories(../idaq2root/include)
include_directories(../core/include)
add_library(${LIB_NAME} SHARED ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core idaq_data_lib)
target_link_libraries(${COMPASS_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core idaq_data_lib ${LIB_NAME})


install(TARGETS ${COMPASS_EXE}
		RUNTIME DESTINATION bin
		)
install(TARGETS ${LIB_NAME}
		LIBRARY DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)