#include <iostream>
#include "TSScanDataLinkDef.h"
#include "YamlParameter.hpp"
#include "IDaqBigRIPSLUPOTSScanner.hpp"
#include "BigRIPSTSScanner.hpp"
#include "TreeMerger.hpp"
#include "OutputTreeData.hpp"

/** prints usage **/
void usage(char *argv0)
{
	std::cout << "[BigRIPSTSMergerMain]: Usage: "
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
			std::cout << "[BigRIPSTSMergerMain]: merging BigRIPS TS to Isobe DAQ TS..." << std::endl;

			/** timestamp scanors **/
			BigRIPSTSScanner BigRIPS_ts_scanner;
			IDaqBigRIPSLUPOTSScanner idaq_ts_scanner;

			/** configures timestamp scanners with the yaml file **/
			BigRIPS_ts_scanner.Configure("BigRIPSTSScanner");
			idaq_ts_scanner.Configure("IDaqBigRIPSLUPOTSScanner");

			/** sets TTreeReaderValue objects **/
			BigRIPS_ts_scanner.SetReader();
			idaq_ts_scanner.SetReader();

			/** scans timestamps through the tree **/
			std::cout << "[BigRIPSTSMergerMain]: scanning BigRIPS events..." << std::endl;
			BigRIPS_ts_scanner.Scan();
			std::cout << "[BigRIPSTSMergerMain]: scanning Isobe DAQ events..." << std::endl;
			idaq_ts_scanner.Scan();

			std::cout << "[BigRIPSTSMergerMain]: BigRIPS map size: " << BigRIPS_ts_scanner.GetIEntryMap().size() << std::endl;
			std::cout << "[BigRIPSTSMergerMain]: Isobe DAQ map size: " << idaq_ts_scanner.GetIEntryMap().size() << std::endl;

			/** runs merger **/
			TreeMerger<OutputTreeData<IDaqData, ULong64_t>, IDaqData, ULong64_t> BigRIPS_ts_merger(&idaq_ts_scanner, &BigRIPS_ts_scanner, true);
			BigRIPS_ts_merger.Configure("BigRIPSTSMerger");
			BigRIPS_ts_merger.Merge();
			BigRIPS_ts_merger.Write();

			std::cout << std::endl;
			std::cout << std::endl;
		}

		/** destroys YamlParameter instance **/
		// YamlParameter::Destroy();
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		std::cout << "[BigRIPSTSMergerMain]: exiting from main() due to an error" << std::endl;
		return 1;
	}
	catch (std::bad_alloc)
	{
		std::cout << "[BigRIPSTSMergerMain]: bad_alloc occured while setting up." << std::endl;
		std::cout << "[BigRIPSTSMergerMain]: exiting from main() due to the error" << std::endl;
		return 1;
	}

	return 0;
}