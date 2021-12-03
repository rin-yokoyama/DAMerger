/**
 * @file GrapeDataDumpMain.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Main file for dumping a part of Grape tree data.
 * @version 0.1
 * @date 2021-12-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "TFile.h"
#include "TTree.h"
#include "TROOT.h"
#include "TChain.h"
#include "GrapeData.hpp"
#include "GrapeDataDumpSelector.hpp"

/** prints usage **/
void usage(char *argv0)
{
	std::cout << "[GrapeDataDumpMain]: Usage: \n"
			  << argv0 << " -i [input_file_name]\n"
			  << "-o [output_file_name] (default: [input_file_name]_dump.root)"
			  << std::endl;
}

int main(int argc, char **argv)
{
	std::string input_file_name = "default";
	std::string output_file_name = "default";

	/** parsing commandline arguments **/
	if (argc < 3)
	{
		usage(argv[0]);
		return 1;
	}
	int opt = 0;
	while ((opt = getopt(argc, argv, "i:o:c:")) != -1)
	{
		switch (opt)
		{
		case 'i':
			input_file_name = optarg;
			break;
		case 'o':
			output_file_name = optarg;
			break;
		default:
			usage(argv[0]);
			return 1;
			break;
		}
	}
	if (input_file_name == "default")
	{
		std::cerr << "[GrapeDataDumpMain]: No input file specified\nexitting..." << std::endl;
		return 1;
	}
	if (output_file_name == "default")
	{
		output_file_name = input_file_name.substr(0, -4) + "_dump.root";
	}

	// Switch to the batch mode.
	gROOT->SetBatch();

	// Create a TChain from the input file.
	TChain *chain = new TChain("build");
	chain->AddFile(input_file_name.c_str());
	std::cout << "[GrapeDataDumpMain]: Added file " << input_file_name << std::endl;

	// Run on PROOF is not implemented for this selector
	{
		// When you don't use PROOF, create a TSelector instance, set parameters you need and run.
		GrapeDataDumpSelector *selector = new GrapeDataDumpSelector(chain);
		selector->SetOutputFileName(output_file_name);
		std::cout << "[GrapeDataDumpMain]: Start processing..." << std::endl;
		chain->Process(selector);
		std::cout << "[GrapeDataDumpMain]: Process done. Exiting..." << std::endl;
		delete selector;
	}

	delete chain;
	return 0;
}