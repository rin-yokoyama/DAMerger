#include "IDaqMyriadTSScanner.hpp"

const std::string IDaqMyriadTSScanner::kMsgPrefix("[IDaqMyriadTSScanner]:");

void IDaqMyriadTSScanner::SetReader()
{
	TSScannerBase<IDaqData>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<IDaqData>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t IDaqMyriadTSScanner::IsInGate()
{
	return true;
}