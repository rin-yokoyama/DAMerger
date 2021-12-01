/**
 * @file YamlReader.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Config file reader in yaml 
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __DAMERGER_YAMLREADER_HPP__
#define __DAMERGER_YAMLREADER_HPP__

#include <iostream>
#include "YamlParameter.hpp"

class YamlReader
{
public:
	YamlReader() {}
	YamlReader(const std::string &yaml_node_name);
	~YamlReader() {}

	YAML::Node GetNode(const std::string &attr, const bool &throw_error = true) const;
	std::string GetString(const std::string &attr, const bool &throw_error = true, const std::string &default_str = "default") const;
	unsigned long long GetULong64(const std::string &attr, const bool &throw_error = true, const unsigned long long &default_val = 0) const;
	double GetDouble(const std::string &attr, const bool &throw_error = true, const double &default_val = 0) const;
	double GetBoolean(const std::string &attr, const bool &throw_error = true, const bool &default_val = false) const;
	std::vector<double> GetDoubleVec(const std::string &attr, const bool &throw_error = true, const std::vector<double> &default_val = {0, 0, 0}) const;
	std::vector<std::string> GetStringVec(const std::string &attr, const bool &throw_error = true, const std::vector<std::string> &default_val = {"", "", ""}) const;

private:
	const static std::string kMsgPrefix;
	YAML::Node yaml_;
};

#endif /** __DAMERGER_YAMLREADER_HPP__ **/