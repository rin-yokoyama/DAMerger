#include "IDaqCompassLUPOTSScanner.hpp"

class IDaqData;

const std::string IDaqCompassLUPOTSScanner::kMsgPrefix("[IDaqCompassLUPOTSScanner]:");

void IDaqCompassLUPOTSScanner::SetReader()
{
	TSScannerBase<IDaqData>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<IDaqData>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t IDaqCompassLUPOTSScanner::IsInGate()
{
	return true;
}