/**
 * @file YamlReader.cpp
 * @author Rin Yokoyama (yokoyama@cns.s.u-tokyo.ac.jp)
 * @brief Config file reader in yaml
 * @version 0.1
 * @date 2021-11-30
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "YamlReader.hpp"

const std::string YamlReader::kMsgPrefix("[YamlReader]:");

YamlReader::YamlReader(const std::string &yaml_node_name)
{
	try
	{
		if (!YamlParameter::GetInstance())
			throw kMsgPrefix + "GetInstance() called but no instant created.";
		yaml_ = YamlParameter::GetInstance()[yaml_node_name];
		if (!yaml_)
		{
			throw kMsgPrefix + "No node named \"" + yaml_node_name + "\" found in the config file.";
		}
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
}

YAML::Node YamlReader::GetNode(const std::string &attr, const bool &throw_error) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			else
			{
				std::cout << kMsgPrefix << "No node named \"" + attr + "\" found in the config file." << std::endl;
				return *(new YAML::Node(""));
			}
		}
		std::cout << kMsgPrefix << "Loaded " << attr << std::endl;
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr];
}

std::string YamlReader::GetString(const std::string &attr, const bool &throw_error, const std::string &default_str) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value " << attr << " = " << default_str << std::endl;
				return default_str;
			}
		}
		std::cout << kMsgPrefix << "Loaded " << attr << " = " << yaml_[attr].as<std::string>() << std::endl;
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<std::string>();
}

unsigned long long YamlReader::GetULong64(const std::string &attr, const bool &throw_error, const unsigned long long &default_val) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value " << attr << " = " << default_val << std::endl;
				return default_val;
			}
		}
		std::cout << kMsgPrefix << "Loaded " << attr << " = " << yaml_[attr].as<unsigned long long>() << std::endl;
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<unsigned long long>();
}

double YamlReader::GetDouble(const std::string &attr, const bool &throw_error, const double &default_val) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value " << attr << " = " << default_val << std::endl;
				return default_val;
			}
		}
		std::cout << kMsgPrefix << "Loaded " << attr << " = " << yaml_[attr].as<double>() << std::endl;
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<double>();
}

double YamlReader::GetBoolean(const std::string &attr, const bool &throw_error, const bool &default_val) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value " << attr << " = " << default_val << std::endl;
				return default_val;
			}
		}
		std::cout << kMsgPrefix << "Loaded " << attr << " = " << yaml_[attr].as<bool>() << std::endl;
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<bool>();
}

std::vector<double> YamlReader::GetDoubleVec(const std::string &attr, const bool &throw_error, const std::vector<double> &default_val) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value" << std::endl;
				return default_val;
			}
		}
		for (const auto &item : yaml_[attr].as<std::vector<double>>())
		{
			std::cout << kMsgPrefix << "Loaded " << attr << " - " << item << std::endl;
		}
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<std::vector<double>>();
}

std::vector<std::string> YamlReader::GetStringVec(const std::string &attr, const bool &throw_error, const std::vector<std::string> &default_val) const
{
	try
	{
		if (!yaml_[attr])
		{
			if (throw_error)
			{
				throw kMsgPrefix + "No node named \"" + attr + "\" found in the config file.";
			}
			else
			{
				std::cout << kMsgPrefix << "Loaded default value" << std::endl;
				return default_val;
			}
		}
		for (const auto &item : yaml_[attr].as<std::vector<std::string>>())
		{
			std::cout << kMsgPrefix << "Loaded " << attr << " - " << item << std::endl;
		}
	}
	catch (YAML::Exception &e)
	{
		std::cout << kMsgPrefix << "exception " << e.what() << std::endl;
		throw;
	}
	catch (std::string msg)
	{
		std::cout << msg << std::endl;
		throw;
	}
	return yaml_[attr].as<std::vector<std::string>>();
}