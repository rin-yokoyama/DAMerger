#ifdef __CINT__

//#pragma link off all globals;
//#pragma link off all classes;
//#pragma link off all functions;

#pragma link C++ class std::vector < ULong64_t> + ;
//#pragma link C++ class Mode3Hit + ;
//#pragma link C++ class Mode3Event + ;
//#pragma link C++ class std::vector < Mode3Hit> + ;
//#pragma link C++ class std::vector < Mode3Event> + ;
#pragma link C++ class OutputTreeData < ULong64_t, ULong64_t> + ;
#pragma link C++ class OutputTreeData < IDaqData, ULong64_t> + ;
#pragma link C++ class OutputTreeData < IDaqData, Mode3Event> + ;

#endif
