#include "GrapeTSScanner.hpp"

const std::string GrapeTSScanner::kMsgPrefix("[GrapeTSScanner]:");

void GrapeTSScanner::SetReader()
{
	TSScannerBase<GrapeData>::SetReader();
	std::string br_name = yaml_reader_->GetString("BranchName");
	tree_data_ = new TTreeReaderValue<GrapeData>(*tree_reader_, br_name.c_str());
	std::cout << kMsgPrefix << "TTreeReaderValue: " << br_name << " created." << std::endl;
	return;
}

Bool_t GrapeTSScanner::IsInGate()
{
	if (tree_data_->Get()->GetHasIDaqTS())
		return true;
	return false;
}