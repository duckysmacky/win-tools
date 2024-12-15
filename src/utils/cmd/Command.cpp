#include "Command.h"

#include <format>

#include "../string-utils.h"

namespace utils
{
	Command::Command(int argc, const char* argv[])
		: m_name("Unknown"), m_version("Unknown"), m_nextArgument(0)
	{
		for (int i = 1; i < argc; i++)
			m_commandArgs.push_back(argv[i]);

		m_options.reserve(2);
		m_options.push_back(CommandOption("help", CommandOption::MESSAGE)
			.setDescription("Shows help information about this command")
			.setShortFlag('h')
		);
		m_options.push_back(CommandOption("version", CommandOption::MESSAGE)
			.setDescription("Shows version information for this command")
			.setShortFlag('V')
		);
	}

	Command& Command::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	Command& Command::addArgument(CommandArgument argument)
	{
		m_arguments.push_back(argument);
		return *this;
	}

	Command& Command::addOption(CommandOption option)
	{
		m_options.push_back(option);
		return *this;
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

		std::string arguments = "\nArguments:\n";
		for (const CommandArgument& argument : m_arguments)
		{
			std::string argumentLabel = toUppercase(argument.id());

			helpMessage += (argument.required())
				? std::format(" <{}>", argumentLabel)
				: std::format(" [{}]", argumentLabel);
			helpMessage += (argument.multiple())
				? "...\n"
				: "\n";

			arguments += std::format("\n\t{} {10:}", argumentLabel, argument.description());
		}
		helpMessage += arguments;
		
		std::string options = "\nOptions:\n";
		for (const CommandOption& option : m_options)
		{
			std::string optionLabel = "--" + option.id();
			
			if (option.hasShortFlag())
				optionLabel += std::format(", -{}", option.shortFlag());
			if (option.hasArgument())
				optionLabel += std::format(" <{}>", toUppercase(option.argument().value().id()));

			options += std::format("\n\t{} {10:}", optionLabel, option.description());
		}
		helpMessage += options;

		return helpMessage;
	}

	void Command::parse()
	{
		// Set default option values
		for (int i = 0; i < m_options.size(); i++)
			m_flagValues.insert({ m_options[i].id(), m_options[i].value() });

		for (int i = 0; i < m_commandArgs.size(); i++)
		{
			std::string arg = m_commandArgs[i];
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
		CommandArgument argument = m_arguments[m_nextArgument];
		
		if (!argument.multiple())
		{
			m_singleValues.insert({argument.id(), m_commandArgs[i]});
		}
		else
		{
			while (i < m_commandArgs.size())
			{
				m_multipleArguments.insert({ argument.id(), std::vector<std::string>() });
				m_multipleArguments[argument.id()].push_back(m_commandArgs[i]);
				i++;
			}
		}

		m_nextArgument++;
	}

	void Command::handleShortFlag(int i)
	{
		std::string argFlag = m_commandArgs[i];

		for (int i = 1; i < argFlag.size(); i++)
		{
			CommandOption option = findOption(argFlag[i]);
			
			if (option.type() == CommandOption::MESSAGE)
			{
				// TODO: exit process
			}

			if (option.hasArgument())
			{
				CommandArgument argument = option.argument().value();
				size_t arg_i = (size_t)(i + 1);

				// Check if there is an argument after the flag
				if (m_arguments.size() - 1 >= arg_i)
				{
					m_singleValues.insert({argument.id(), m_commandArgs[arg_i]});
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
	}

	void Command::handleLongFlag(int i)
	{
		CommandOption option = findOption(m_commandArgs[i].substr(2));
		
		if (option.type() == CommandOption::MESSAGE)
		{
			// TODO: exit process
		}

		if (option.hasArgument())
		{
			CommandArgument argument = option.argument().value();
			size_t arg_i = (size_t)(i + 1);

			if (m_arguments.size() - 1 >= arg_i)
			{
				m_singleValues.insert({argument.id(), m_commandArgs[arg_i]});
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

	CommandOption Command::findOption(const std::string& longFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].id() == longFlag)
				return m_options[i];
		}

		// TODO: throw error (unknown option)
	}

	CommandOption Command::findOption(char shortFlag)
	{
		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].shortFlag() == shortFlag)
				return m_options[i];
		}

		// TODO: throw error (unknown option)
	}
}
