/**
 * @file GrapeDataDumpSelector.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief ROOT TSelector class for scanning and dumping grape data for merge
 * @version 0.1
 * @date 2021-12-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __DAMERGER_GRAPE_DATA_DUMP_SELECTOR_HPP__
#define __DAMERGER_GRAPE_DATA_DUMP_SELECTOR_HPP__
#include <iostream>
#include <string>
#include "TSelector.h"
#include "TTree.h"
#include "TProofServ.h"
#include "TProofOutputFile.h"
#include "TFile.h"
#include "TParameter.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include "TH1.h"
#include "GrapeData.hpp"
#include "Trace.hh"

class GrapeDataDumpSelector : public TSelector
{
public:
	GrapeDataDumpSelector(TTree *tree = 0);
	virtual ~GrapeDataDumpSelector();

	// Overloaded from TSelector
	virtual Int_t Version() const { return 1; }
	virtual void Init(TTree *tree);
	virtual void Begin(TTree *tree);
	virtual void SlaveBegin(TTree *tree);
	virtual Bool_t Notify()
	{
		std::cout << "Notify() called." << std::endl;
		return kTRUE;
	}
	virtual Bool_t Process(Long64_t entry);
	virtual void SetOption(const char *option) { fOption = option; }
	virtual void SetObject(TObject *obj) { fObject = obj; }
	virtual void SetInputList(TList *input) { fInput = input; }
	virtual TList *GetOutputList() const { return fOutput; }
	virtual void SlaveTerminate();
	virtual void Terminate();

	// Set methods
	void SetOutputFileName(const std::string &name) { output_file_name_ = name; }
	void SetParameter(const Double_t &parameter) { parameter_ = parameter; }

protected:
	TTreeReader tree_reader_;				// TTreeReader for the input tree
	TTreeReaderValue<Mode3Event> data_;		// TTreeReaderValue for the input data branch
	TTree *fOutputTree = nullptr;			// A pointer to the output tree object
	TFile *fOutputFile = nullptr;			// A pointer to the output file object
	TProofOutputFile *fProofFile = nullptr; // A pointer to the ProofOutputFile object
	std::string output_file_name_;			// The output file name
	Double_t parameter_;					// An example parameter to process data
	Bool_t merge_tree_ = false;				// A flag whether to merge tree output at the end when use PROOF.
	GrapeData output_data_;					// The output data that will be filled to the tree

	ClassDef(GrapeDataDumpSelector, 1)
};

#endif