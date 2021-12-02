#include <iostream>
#include "TSScanDataLinkDef.h"
#include "YamlParameter.hpp"
#include "IDaqMyriadTSScanner.hpp"
#include "HicariTSScanner.hpp"
#include "TreeMerger.hpp"
#include "OutputTreeData.hpp"
#include "Trace.hh"

/** prints usage **/
void usage(char *argv0)
{
	std::cout << "[HicariTSMergerMain]: Usage: "
			  << argv0 << "-c [configuration_file_name]"
			  << std::endl;
}

int main(int argc, char **argv)
{
	std::string input_file_name;
	std::string config_file_name;
	std::string output_file_name;

	/** parsing commandline arguments **/
	if (argc != 3)
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
		case 'c':
			config_file_name = optarg;
			break;
		default:
			usage(argv[0]);
			return 1;
			break;
		}
	}

	try
	{
		/** creates YamlParameter instance **/
		YamlParameter::Create(config_file_name);

		/** merges BigRIPS events to implant events **/
		{
			std::cout << "[HicariTSMergerMain]: merging hicari TS to Isobe DAQ TS..." << std::endl;

			/** timestamp scanors **/
			HicariTSScanner hicari_ts_scanner;
			IDaqMyriadTSScanner idaq_ts_scanner;

			/** configures timestamp scanners with the yaml file **/
			hicari_ts_scanner.Configure("HicariTSScanner");
			idaq_ts_scanner.Configure("IDaqLUPOTSScanner");

			/** sets TTreeReaderValue objects **/
			hicari_ts_scanner.SetReader();
			idaq_ts_scanner.SetReader();

			/** scans timestamps through the tree **/
			std::cout << "[HicariTSMergerMain]: scanning Hicari events..." << std::endl;
			hicari_ts_scanner.Scan();
			std::cout << "[HicariTSMergerMain]: scanning Isobe DAQ events..." << std::endl;
			idaq_ts_scanner.Scan();

			std::cout << "[HicariTSMergerMain]: Hicari map size: " << hicari_ts_scanner.GetIEntryMap().size() << std::endl;
			std::cout << "[HicariTSMergerMain]: Isobe DAQ map size: " << idaq_ts_scanner.GetIEntryMap().size() << std::endl;

			/** runs merger **/
			TreeMerger<OutputTreeData<IDaqData, Mode3Event>, IDaqData, Mode3Event> hicari_ts_merger(&idaq_ts_scanner, &hicari_ts_scanner, false);
			hicari_ts_merger.Configure("HicariTSMerger");
			hicari_ts_merger.Merge();
			hicari_ts_merger.Write();

			std::cout << std::endl;
			std::cout << std::endl;
		}

		/** destroys YamlParameter instance **/
		//YamlParameter::Destroy();
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		std::cout << "[HicariTSMergerMain]: exiting from main() due to an error" << std::endl;
		return 1;
	}
	catch (std::bad_alloc)
	{
		std::cout << "[HicariTSMergerMain]: bad_alloc occured while setting up." << std::endl;
		std::cout << "[HicariTSMergerMain]: exiting from main() due to the error" << std::endl;
		return 1;
	}

	return 0;
}