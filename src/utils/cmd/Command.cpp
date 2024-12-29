#include "./Command.h"

#include <format>

#include "utils.h"

namespace cmd
{
	Command::Command(
		const std::string& name,
		const std::string& version,
		const std::vector<std::string>& commandArgs,
		const std::vector<Argument>& arguments,
		const std::vector<Option>& options
	) :
		m_name(name),
		m_version(version),
		m_commandArgs(commandArgs),
		m_arguments(arguments),
		m_options(options),
		m_nextArgument(0)
	{
		// Set default option values
		for (int i = 0; i < m_options.size(); i++)
		{
			Option option = m_options[i];

			if (option.type() == Option::ARGUMENT)
			{
				m_singleValues.insert({ option.id(), option.defaultValue() });
			}

			m_flagValues.insert({ option.id(), false });
		}

		// Parse command arguments
		for (int i = 0; i < m_commandArgs.size(); i++)
		{
			std::string arg = m_commandArgs[i];

			if (arg.empty()) continue;

			// if starts with a dash
			if (arg[0] == '-' && arg.length() > 1)
			{
				// if starts with a double dash
				if (arg[1] == '-' && arg.length() > 2)
				{
					handleLongFlag(i);
				}
				else
				{
					handleShortFlag(i);
				}
			}
			else
			{
				handleArgument(i);
			}
		}

		// Check if any required arguments are not supplied
		if (m_nextArgument < m_arguments.size())
		{
			Argument argument = m_arguments[m_nextArgument];

			if (argument.required() && !(argument.multiple() && m_multipleValues.size() > 0))
			{
				utils::logError(std::format("Required argument <{}> was not provided", utils::toUppercase(argument.id())));
				std::exit(0);
			}
		}
	}

	bool Command::hasValue(const std::string& id) const
	{
		return m_singleValues.contains(id);
	}

	bool Command::hasMultiple(const std::string& id) const
	{
		return m_multipleValues.contains(id);
	}

	std::string Command::getValue(const std::string& id) const
	{
		if (!m_singleValues.contains(id))
		{
			utils::logError(std::format("Value with ID \"{}\" not found", id));
			std::exit(1);
		}
		return m_singleValues.at(id);
	}

	std::vector<std::string> Command::getMultiple(const std::string& id) const
	{
		if (!m_multipleValues.contains(id))
		{
			utils::logError(std::format("Values with ID \"{}\" not found", id));
			std::exit(1);
		}
		return m_multipleValues.at(id);
	}

	bool Command::getFlag(const std::string& id) const
	{
		if (!m_flagValues.contains(id))
		{
			utils::logError(std::format("Flag with ID \"{}\" not found", id));
			std::exit(1);
		}
		return m_flagValues.at(id);
	}
	
	std::string Command::name() const
	{
		return m_name;
	}

	std::string Command::version() const
	{
		return m_version;
	}

	/* PRIVATE */

	void Command::handleArgument(int i)
	{
		if (m_nextArgument > m_arguments.size() - 1)
		{
			utils::logError(std::format("Unknown argument \"{}\"", m_commandArgs[i]));
			std::exit(1);
		}

		Argument argument = m_arguments[m_nextArgument];
		
		if (!argument.multiple())
		{
			m_singleValues.insert({argument.id(), m_commandArgs[i]});
			m_nextArgument++;
		}
		else
		{
			if (m_multipleValues.count(argument.id()) == 0)
			{
			m_multipleValues.insert({ argument.id(), std::vector<std::string>() });
			}

			m_multipleValues[argument.id()].push_back(m_commandArgs[i]);
		}
	}

	void Command::handleShortFlag(int i)
	{
		std::string argFlag = m_commandArgs[i];

		for (int j = 1; j < argFlag.size(); j++)
		{
			Option option = findOption(argFlag[j]);
			handleOption(option, i);
		}
	}

	void Command::handleLongFlag(int i)
	{
		Option option = findOption(m_commandArgs[i].substr(2));
		handleOption(option, i);
	}

	void Command::handleOption(const Option& option, int i)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			Option other_option = m_options[i];

			if (other_option.id() == option.id()) continue;

			if (other_option.conflicts().contains(option.id()) && m_flagValues[other_option.id()])
			{
				utils::logError(std::format("Option \"{}\" conficts with \"{}\"", option.id(), other_option.id()));
				std::exit(1);
			}
		}

		switch (option.type())
		{
		// In case of a message option, simply display it and exit
		case Option::MESSAGE:
		{
			std::cout << option.message() << std::endl;
			std::exit(0);
			break;
		}
		case Option::ARGUMENT:
		{
			Argument argument = option.argument();
			size_t arg_i = (size_t)(i + 1);

			// Check if there is an argument after the flag
			if (m_commandArgs.size() - 1 >= arg_i)
			{
				m_singleValues[argument.id()] = m_commandArgs[arg_i];
				m_commandArgs[arg_i] = "";
			}
			else
			{
				utils::logError(std::format("Required option argument for {} was not provided", option.id()));
				std::exit(1);
			}
			break;
		}
		default:
		{
			m_flagValues[option.id()] = true;
			break;
		}
		}
	}

	Option Command::findOption(const std::string& longFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].id() == longFlag)
				return m_options[i];
		}

		utils::logError(std::format("Unknown option \"{}\"", longFlag));
		std::exit(1);
	}

	Option Command::findOption(char shortFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].shortFlag() == shortFlag)
				return m_options[i];
		}

		utils::logError(std::format("Unknown option \"{}\"", shortFlag));
		std::exit(1);
	}
}

