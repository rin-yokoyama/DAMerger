/**
 * @file idaq2root_main.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief main cpp for Isobe DAQ data to ROOT converter
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include "TArtEventStore.hh"
#include "TArtRawEventObject.hh"
#include "IDaqData.hpp"
#include "TFile.h"
#include "TTree.h"

/** prints usage **/
void usage(char *argv0)
{
	std::cout << "[IDaq2ROOTMain]: Usage: \n"
			  << argv0 << " -i [input_ridf_file_name]\n"
			  << "-o [output_root_file_name] (default: [input_ridf_file_name].root)"
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
		std::cerr << "[IDaq2ROOTMain]: No input file specified\nexitting..." << std::endl;
		return 1;
	}
	if (output_file_name == "default")
	{
		output_file_name = input_file_name.substr(0, -4) + ".root";
	}

	/// Open the input ridf file using anaroot
	TArtEventStore *estore = new TArtEventStore();
	std::cout << "[IDaq2ROOTMain]: Opening input file " << input_file_name << std::endl;
	estore->Open(input_file_name.c_str());
	TArtRawEventObject *rawevent = estore->GetRawEventObject();

	/// Open the output root file
	std::cout << "[IDaq2ROOTMain]: Opening output file " << output_file_name << std::endl;
	TFile output_file(output_file_name.c_str(), "recreate");
	TTree tree("tree", "IDAQTree"); /// output tree
	IDaqData data;					/// output data container object
	tree.Branch("IDaqData", "IDaqData", &data);

	ULong64_t first_lupots = 0;
	ULong64_t first_myriadts = 0;
	while (estore->GetNextEvent())
	{
		ULong64_t lupo_ts;
		ULong64_t myriad_ts;
		/// event loop
		for (int i = 0; i < rawevent->GetNumSeg(); ++i)
		{
			TArtRawSegmentObject *seg = rawevent->GetSegment(i);
			int det = seg->GetDetector();
			int mod = seg->GetModule();

			/// function to read timestamp data
			auto get_ts = [seg]()
			{
				TArtRawDataObject *d = seg->GetData(0);
				ULong64_t valh = d->GetVal();
				d = seg->GetData(1);
				ULong64_t vall = d->GetVal();
				return (valh << 32) + vall;
			};

			if (det == 60)
			{ // LUPO
				lupo_ts = get_ts() - first_lupots;
			}

			if (det == 49)
			{ // MYRIAD
				myriad_ts = get_ts() - first_myriadts;
			}

		} // for(int i=0;i<rawevent->GetNumSeg();i++)

		if (first_lupots == 0 && first_myriadts == 0)
		{
			first_lupots = lupo_ts;
			first_myriadts = myriad_ts;
		}

		data.SetTimestamps(lupo_ts, myriad_ts);
		tree.Fill();

		estore->ClearData();
	}
	tree.Write();
	output_file.Close();
	return 0;
}