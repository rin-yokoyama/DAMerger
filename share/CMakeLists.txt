configure_file("modulefiles/DAMerger" DAMerger @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/DAMerger DESTINATION share/modulefiles/)