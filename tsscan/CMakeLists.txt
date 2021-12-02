include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/idaq2root/include)
include_directories(${CMAKE_SOURCE_DIR}/core/include)

ROOT_GENERATE_DICTIONARY(G__TSScanData include/OutputTreeData.hpp ${CMAKE_SOURCE_DIR}/idaq2root/include/IDaqData.hpp ${GRETINA_DECODER_DIR}/cmake/inc/inc/Trace.hh LINKDEF include/TSScanDataLinkDef.h)
set(LIB_NAME TSScan)
set(LIB_SOURCES
	source/IDaqMyriadTSScanner.cpp
	source/IDaqLUPOTSScanner.cpp
	source/CompassTSScanner.cpp
	source/HicariTSScanner.cpp
	G__TSScanData.cxx
)
set(COMPASS_EXE compass_ts_merger)
set(HICARI_EXE hicari_ts_merger)

add_library(${LIB_NAME} SHARED ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core idaq_data_lib HiCARI)
add_executable(${COMPASS_EXE} source/CompassTSMergerMain.cpp)
target_link_libraries(${COMPASS_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core idaq_data_lib ${LIB_NAME})
add_executable(${HICARI_EXE} source/HicariTSMergerMain.cpp)
target_link_libraries(${HICARI_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core idaq_data_lib ${LIB_NAME} HiCARI)


install(TARGETS ${COMPASS_EXE} ${HICARI_EXE}
		RUNTIME DESTINATION bin
		)
install(TARGETS ${LIB_NAME}
		LIBRARY DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)