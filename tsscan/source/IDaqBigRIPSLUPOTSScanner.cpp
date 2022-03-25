#include "IDaqBigRIPSLUPOTSScanner.hpp"

class IDaqData;

const std::string IDaqBigRIPSLUPOTSScanner::kMsgPrefix("[IDaqBigRIPSLUPOTSScanner]:");

void IDaqBigRIPSLUPOTSScanner::SetReader()
{
	TSScannerBase<IDaqData>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<IDaqData>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t IDaqBigRIPSLUPOTSScanner::IsInGate()
{
	return true;
}