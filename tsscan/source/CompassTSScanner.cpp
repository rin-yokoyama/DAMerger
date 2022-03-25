#include "CompassTSScanner.hpp"

const std::string CompassTSScanner::kMsgPrefix("[CompassTSScanner]:");

void CompassTSScanner::SetReader()
{
	TSScannerBase<ULong64_t>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<ULong64_t>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t CompassTSScanner::IsInGate()
{
	// Int_t ch = *(Int_t *)branch_map_.at("Channel").second;
	// if (ch == 8)
	return true;
}