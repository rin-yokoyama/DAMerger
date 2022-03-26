# DAMerger
Data merger tools for DA05 experiment

## Installation

- Required Prerequisites:
	- [cmake](https://cmake.org/) version 3.17.5 or later is confirmed to work
	- [yaml-cpp](https://github.com/jbeder/yaml-cpp) version 0.6.3 or later is recommended
		- Build option `-DBUILD_SHARED=ON` is required
	- [ROOT](https://root.cern.ch/) version 6 is recommended
	  - Requires xml 
	- [anaroot](https://ribf.riken.jp/RIBFDAQ/index.php?Tools%2FAnalysis%2FANAROOT%2FInstallation) version 4.5.39 is confirmed to work
	- [GretinaDecoder]

```bash
git clone https://github.com/rin-yokoyama/DAMerger.git
cd DAMerger
mkdir build
cd build
ccmake
make install
```

Privide the path to your Gretina Decoder to GRETINA_DECODER_DIR.
ANAROOT_DIR_PATH will be automatically detected if $TARTSYS is defined.

## idaq2root
Data decoder for Isobe DAQ

```Usage:
idaq2root -i [input_ridf_file (required)] -o [output_root_file (default:[input_ridf_file].root)]
```

- Output
  - TTree name: "tree"
  - compass_lupo_ts_
  - brips_lupo_ts_
  - myriad_ts_
  - event_id_

## grape_dump
Dumps GRAPE data for merging

```Usage:
grape_dump -i [input_file (required)] -o [output_file (default:[input_file]_dump.root)]
```

- Output
  - TTree name: OutputTree
  - has_idaq_ts_ (flag if this event has an Isobe DAQ trigger)
  - ts_
  - event_id_

## compass_ts_merger
Merger for Isobe DAQ LUPO timestamps and Compass timestamps

```Usage:
compass_ts_merger -c [config_yaml_file (required)]
```

An example config file will be installed to config/ts_merger_config.yaml

- Output
  - TTree name: TS
  - input_ (Isobe DAQ data)
  - output_vec_ (std::vector<ULong64_t> correlated compass timestamps) 

 ## grape_ts_merger
Merger for Isobe DAQ Myriad timestamps and GRAPE timestamps

```Usage:
grape_ts_merger -c [config_yaml_file (required)]
```

An example config file will be installed to config/ts_merger_config.yaml (It has configuration for both compass_ts_merger and grape_ts_merger)

- Output
  - TTree name: TS
  - input_ (Isobe DAQ data)
  - output_vec_ (std::vector<GrapeData> correlated GrapeData) 
