include_directories(include)
include_directories(${CMAKE_SOURCE_DIR}/idaq2root/include)
include_directories(${CMAKE_SOURCE_DIR}/core/include)
include_directories(${CMAKE_SOURCE_DIR}/grape_dump/include)

ROOT_GENERATE_DICTIONARY(G__TSScanData OutputTreeData.hpp LINKDEF include/TSScanDataLinkDef.h)
set(LIB_NAME TSScanData)
set(LIB_SOURCES
	source/IDaqMyriadTSScanner.cpp
	#source/IDaqBigRIPSLUPOTSScanner.cpp
	source/IDaqCompassLUPOTSScanner.cpp
	source/CompassTSScanner.cpp
	source/GrapeTSScanner.cpp
	G__TSScanData.cxx
)
set(COMPASS_EXE compass_ts_merger)
set(BIGRIPS_EXE bigrips_ts_merger)
set(Grape_EXE grape_ts_merger)

add_library(${LIB_NAME} SHARED ${LIB_SOURCES})
target_link_libraries(${LIB_NAME} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core IDaqData GrapeData HiCARI)
add_executable(${COMPASS_EXE} source/CompassTSMergerMain.cpp)
target_link_libraries(${COMPASS_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core IDaqData ${LIB_NAME})
#add_executable(${BIGRIPS_EXE} source/BigRIPSTSMergerMain.cpp)
#target_link_libraries(${BIGRIPS_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core IDaqData ${LIB_NAME})
add_executable(${Grape_EXE} source/GrapeTSMergerMain.cpp)
target_link_libraries(${Grape_EXE} ${ROOT_LIBRARIES} ${YAML_CPP_LIBRARIES} core IDaqData GrapeData ${LIB_NAME} HiCARI)


install(TARGETS ${COMPASS_EXE} ${Grape_EXE}
		RUNTIME DESTINATION bin
		)
install(TARGETS ${LIB_NAME}
		LIBRARY DESTINATION lib
		)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
		)