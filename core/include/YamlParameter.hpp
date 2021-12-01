/**
 * @file YamlParameter.hpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief singleton class for yaml-cpp
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef __DAMERGER_YAMLPARAMETER_HPP__
#define __DAMERGER_YAMLPARAMETER_HPP__

#include "yaml-cpp/yaml.h"

class YamlParameter : public YAML::Node
{
private:
	YamlParameter(std::string file_name) : YAML::Node(YAML::LoadFile(file_name)) {}
	~YamlParameter() = default;

	static YamlParameter *instance;

public:
	YamlParameter() = delete;
	YamlParameter(const YamlParameter &) = delete;
	YamlParameter &operator=(const YamlParameter &) = delete;
	YamlParameter(YamlParameter &&) = delete;
	YamlParameter &operator=(YamlParameter &&) = delete;

	static YamlParameter &GetInstance()
	{
		return *instance;
	}

	static void Create(std::string file_name)
	{
		if (!instance)
		{
			instance = new YamlParameter(file_name);
		}
	}

	static void Destroy()
	{
		if (instance)
		{
			delete instance;
			instance = NULL;
		}
	}
};

#endif /** __DAMERGER_YAMLPARAMETER_HPP__ **/