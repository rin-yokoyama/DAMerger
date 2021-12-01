#include <iostream>
#include "OutputTreeData.hpp"
#include "TSScanDataLinkDef.h"
#include "YamlParameter.hpp"
#include "IDaqLUPOTSScanner.hpp"
#include "CompassTSScanner.hpp"
#include "TreeMerger.hpp"

/** prints usage **/
void usage(char *argv0)
{
	std::cout << "[CompassTSMergerMain]: Usage: "
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
			std::cout << "[CompassTSMergerMain]: merging compass TS to Isobe DAQ TS..." << std::endl;

			/** timestamp scanors **/
			CompassTSScanner compass_ts_scanner;
			IDaqLUPOTSScanner idaq_ts_scanner;

			/** configures timestamp scanners with the yaml file **/
			compass_ts_scanner.Configure("CompassTSScanner");
			idaq_ts_scanner.Configure("IDaqLUPOTSScanner");

			/** sets TTreeReaderValue objects **/
			compass_ts_scanner.SetReader();
			idaq_ts_scanner.SetReader();

			/** scans timestamps through the tree **/
			std::cout << "[CompassTSMergerMain]: scanning Compass events..." << std::endl;
			compass_ts_scanner.Scan();
			std::cout << "[CompassTSMergerMain]: scanning Isobe DAQ events..." << std::endl;
			idaq_ts_scanner.Scan();

			std::cout << "[CompassTSMergerMain]: Compass map size: " << compass_ts_scanner.GetIEntryMap().size() << std::endl;
			std::cout << "[CompassTSMergerMain]: Isobe DAQ map size: " << idaq_ts_scanner.GetIEntryMap().size() << std::endl;

			/** runs merger **/
			TreeMerger<OutputTreeData<ULong64_t, ULong64_t>, IDaqData, ULong64_t> compass_ts_merger(&idaq_ts_scanner, &compass_ts_scanner, true);
			compass_ts_merger.Configure("CompassTSMerger");
			compass_ts_merger.Merge();
			compass_ts_merger.Write();

			std::cout << std::endl;
			std::cout << std::endl;
		}

		/** destroys YamlParameter instance **/
		//YamlParameter::Destroy();
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		std::cout << "[CompassTSMergerMain]: exiting from main() due to an error" << std::endl;
		return 1;
	}
	catch (std::bad_alloc)
	{
		std::cout << "[CompassTSMergerMain]: bad_alloc occured while setting up." << std::endl;
		std::cout << "[CompassTSMergerMain]: exiting from main() due to the error" << std::endl;
		return 1;
	}

	return 0;
}