#include "HicariTSScanner.hpp"

const std::string HicariTSScanner::kMsgPrefix("[HicariTSScanner]:");

void HicariTSScanner::SetReader()
{
	TSScannerBase<Mode3Event>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<Mode3Event>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t HicariTSScanner::IsInGate()
{
	if (GetTS() < 1)
		return false;

	return true;
}