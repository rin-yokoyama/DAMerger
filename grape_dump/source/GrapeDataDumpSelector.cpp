/**
 * @file GrapeDataDumpSelector.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief 
 * @version 0.1
 * @date 2021-12-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "GrapeDataDumpSelector.hpp"

ClassImp(GrapeDataDumpSelector)

	GrapeDataDumpSelector::GrapeDataDumpSelector(TTree *tree) : tree_reader_(tree),
																data_(tree_reader_, "mode3Event"),
																output_file_name_("default_name"),
																parameter_(0)
{
}

GrapeDataDumpSelector::~GrapeDataDumpSelector()
{
	if (fOutputFile)
		delete fOutputFile;
}

void GrapeDataDumpSelector::Begin(TTree *tree)
{
	// Begin() is called only in the client process.
	// Get OutputFileName from the list of input objects.
	// This is required when you write a file in the Terminate() method.
	if (fInput)
	{
		TNamed *named = (TNamed *)fInput->FindObject("OutputFileName");
		if (named)
			output_file_name_ = named->GetTitle();
	}
}

void GrapeDataDumpSelector::SlaveBegin(TTree *tree)
{
	// SlaveBegin() is called only in the worker process when it runs on PROOF.
	// If it's not on PROOF, SlaveBegin() is called after Begin()

	// Clear the fOutputList.
	// fOutputList is a list of object which will be merged and sent to the client process.
	GetOutputList()->Clear();

	if (gProofServ)
	{
		// If this process is running on a PROOF server, read objects from fInput.
		if (fInput)
		{
			TNamed *named = (TNamed *)fInput->FindObject("OutputFileName");
			if (named)
				output_file_name_ = named->GetTitle();
			TParameter<Double_t> *parameter = (TParameter<Double_t> *)fInput->FindObject("Parameter");
			if (parameter)
				parameter_ = parameter->GetVal();
			TParameter<Bool_t> *merge_tree = (TParameter<Bool_t> *)fInput->FindObject("MergeTree");
			if (merge_tree)
				merge_tree_ = merge_tree->GetVal();
		}

		// Create a TProofOutputFile
		if (fProofFile)
			delete fProofFile;
		if (merge_tree_)
		{
			// Option "M" to merge files from all the workers at the end
			fProofFile = new TProofOutputFile(output_file_name_.c_str(), "M");
		}
		else
		{
			// Without "M" not to merge output
			fProofFile = new TProofOutputFile(output_file_name_.c_str(), "");
		}

		// Open an output file for this worker.
		fProofFile->SetOutputFileName(output_file_name_.c_str());
		if (fOutputFile)
			delete fOutputFile;
		fOutputFile = fProofFile->OpenFile("RECREATE");

		// You can send a message to the client process from workers by using SendAsynMessage()
		const TString msg = TString::Format("SalveBegin() of Ord = %s is called.", gProofServ->GetOrdinal());
		gProofServ->SendAsynMessage(msg);
	}
	else
	{
		// If it's not on PROOF, just create a new file.
		std::cout << "[GrapeDataDumpSelector]: Proof is off." << std::endl;
		if (fOutputFile)
			delete fOutputFile;
		fOutputFile = new TFile(output_file_name_.c_str(), "RECREATE");
		std::cout << "[GrapeDataDumpSelector]: An output file created " << output_file_name_ << std::endl;
	}

	// Create an output tree.
	if (fOutputTree)
		delete fOutputTree;
	fOutputTree = new TTree("OutputTree", "OutputTree");
	fOutputTree->Branch("grape_dumped", "GrapeDumpData", &output_data_);
	fOutputTree->SetDirectory(fOutputFile);
	fOutputTree->AutoSave();
}

void GrapeDataDumpSelector::Init(TTree *tree)
{
	// Init() is called when the selector needs to initialize a new tree
	// According to the ROOT documentation, the tree argument of the Begin()
	// and SlaveBegin() functions is deprecated.
	// Therefore, SetTree() should be called in this function.
	tree_reader_.SetTree(tree);
}

Bool_t GrapeDataDumpSelector::Process(Long64_t entry)
{
	// Process() is called for each entry in the tree.
	// This function should contain the body of the analysis.

	tree_reader_.SetLocalEntry(entry);

	// "data" is a pointer to the ExampleData branch object.
	auto data = data_.Get();

	if (!data)
		return kTRUE;

	GrapeData gr_data;
	for (int i = 0; i < data->GetMult(); ++i)
	{
		auto &trace0 = data->GetHit(i)->GetTrace()->at(0);
		auto hole = trace0.GetHole();
		auto crystal = trace0.GetCrystal();
		auto slot = trace0.GetSlot();
		auto chn = trace0.GetChn();
		if (hole == 11 && crystal == 0 && slot == 2 && chn == 9)
		{
			gr_data.SetTimestamp(trace0.GetTS());
		}
	};

	output_data_ = gr_data;
	// Fill the tree and the histogram
	fOutputTree->Fill();

	return kTRUE;
}

void GrapeDataDumpSelector::SlaveTerminate()
{
	// SlaveTerminate() is called after all entries have been processed.
	// This function is called only in the worker process.
	// If it's not on PROOF, SlaveTerminate() is called before Terminate()

	if (!gProofServ)
		std::cout << "[GrapeDataDumpSelector]: Writing Tree to the output file..." << std::endl;
	// Unlink the tree reader from the input tree.
	tree_reader_.SetTree((TTree *)nullptr);

	// Write the tree and the histogram to file.
	fOutputFile->cd();
	fOutputTree->Write();

	// If merge_tree_ flag is true, add the file to the fOutput
	// so the files from all the workers will be merged.
	if (merge_tree_)
		fOutput->Add(fProofFile);

	// Close the file.
	fOutputTree->SetDirectory(0);
	fOutputFile->Close();
	delete fOutputFile;
	fOutputFile = nullptr;
}

void GrapeDataDumpSelector::Terminate()
{
	// Terminate() is called only in the client process

	// If there is a histogram in the output list (i.e. merge_tree_ = false),
	// create a file in the client process and write it to the file.
}