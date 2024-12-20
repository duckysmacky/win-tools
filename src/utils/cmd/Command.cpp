#include "./Command.h"

#include <format>
#include <iostream>

#include "utils.h"

namespace cmd
{
	Command::Command(int argc, const char* argv[])
		: m_name("Unknown"), m_version("Unknown"), m_nextArgument(0)
	{
		for (int i = 1; i < argc; i++)
			m_commandArgs.push_back(argv[i]);

		m_options.reserve(2);
		m_options.push_back(Option("help")
			.setDescription("Display help message")
			.setShortFlag('h')
		);
		m_options.push_back(Option("version")
			.setDescription("Display version information")
			.setShortFlag('V')	
		);
	}

	Command& Command::setName(const std::string& name)
	{
		m_name = name;
		return *this;
	}

	Command& Command::setVersion(const std::string& version)
	{
		m_version = version;
		return *this;
	}

	Command& Command::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	Command& Command::addArgument(Argument argument)
	{
		m_arguments.push_back(argument);
		return *this;
	}

	Command& Command::addOption(Option option)
	{
		m_options.push_back(option);
		return *this;
	}

	std::string Command::getValue(const std::string& id) const
	{
		return m_singleValues.at(id);
	}

	std::vector<std::string> Command::getMultiple(const std::string& id) const
	{
		return m_multipleValues.at(id);
	}

	bool Command::getFlag(const std::string& id) const
	{
		return m_flagValues.at(id);
	}
	
	std::string Command::generateVersion() const
	{
		return std::format("{} - v{} (github.com/duckysmacky/win-tools)", m_name, m_version);
	}

	// TODO: support better newlines for terminal width
	std::string Command::generateHelp() const
	{
		/*
			Usage: <name> [OPTIONS]... <REQUIRED> [OPTIONAL] [MULTIPLE]...

			Arguments:
				<REQUIRED>						description
				[OPTIONAL]						description
				[MULTIPLE]...					description

			Options:
				--help, -h						description
				--version, -V					description
				--flag, -f						description
				--value, -v <ARGUMENT>			description
		*/
		
		std::string helpMessage = std::format("Usage: {} [OPTIONS]...", m_name);

		std::string arguments = "\nArguments:";
		for (const Argument& argument : m_arguments)
		{
			std::string argumentLabel = utils::toUppercase(argument.id());

			helpMessage += (argument.required())
				? std::format(" {}", argumentLabel)
				: std::format(" [{}]", argumentLabel);
			helpMessage += (argument.multiple())
				? "...\n"
				: "\n";

			arguments += std::format("\n  {:<25} {}", argumentLabel, argument.description());
		}
		helpMessage += arguments;
		
		std::string options = "\n\nOptions:";
		for (const Option& option : m_options)
		{
			std::string optionLabel = "--" + option.id();
			
			if (option.hasShortFlag())
				optionLabel += std::format(", -{}", option.shortFlag());
			if (option.type() == Option::ARGUMENT)
				optionLabel += std::format(" <{}>",utils::toUppercase(option.argument().id()));

			options += std::format("\n  {:<25} {}", optionLabel, option.description());
		}
		helpMessage += options;

		return helpMessage;
	}

	void Command::parse()
	{
		// Setup default messages
		m_options[0].setMessage(generateHelp());
		m_options[1].setMessage(generateVersion());

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

		// TODO: check if any required arguments are not supplied
	}

	void Command::handleArgument(int i)
	{
		if (m_nextArgument > m_arguments.size() - 1)
		{
			std::cerr << "Error: unknown argument \"" << m_commandArgs[i] << "\"" << std::endl;
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
		if (option.type() == Option::MESSAGE)
		{
			if (option.id() == "help")
			{
				std::cout << generateHelp() << std::endl;
			}
			else if (option.id() == "version")
			{
				std::cout << generateVersion() << std::endl;
			}
			std::exit(0);
		}

		if (option.type() == Option::ARGUMENT)
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
				// TODO: throw error (option argument not provided)
			}
		}
		else
		{
			m_flagValues[option.id()] = true;
		}
	}

	Option Command::findOption(const std::string& longFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].id() == longFlag)
				return m_options[i];
		}

		// TODO: throw error (unknown option)
	}

	Option Command::findOption(char shortFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].shortFlag() == shortFlag)
				return m_options[i];
		}

		// TODO: throw error (unknown option)
	}
}
