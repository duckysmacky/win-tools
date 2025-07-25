#include "CommandBuilder.hpp"

#include "utils/logs.h"
#include "utils/general.h"

#include <format>
#include <iostream>

namespace cmd
{
	CommandBuilder::CommandBuilder(const std::string& name, const std::string& version)
		: m_name(name), m_version(version) 
	{
		m_options.reserve(2);
		m_options.push_back(Option("help")
			.setDescription("Show help information for the command")
			.setShortFlag('h')
		);
		m_options.push_back(Option("version")
			.setDescription("Show version information for the command")
			.setShortFlag('V')
			.setMessage(generateVersion())
		);
	}

	CommandBuilder& CommandBuilder::setDescription(const std::string& description)
	{
		m_description = description;
		return *this;
	}

	CommandBuilder& CommandBuilder::addArgument(Argument argument)
	{
		for (int i = 0; i < m_arguments.size(); i++)
		{
			if (m_arguments[i].id() == argument.id())
			{
				logs::logError(std::format("Argument with id \"{}\" already exists", argument.id()));
				std::exit(1);
			}
		}

		m_arguments.push_back(argument);
		return *this;
	}

	CommandBuilder& CommandBuilder::addOption(Option option)
	{
		if (option.id() == "help" || option.id() == "version")
		{
			logs::logError(std::format("Unable to add option with reserved id \"{}\"", option.id()));
			std::exit(1);
		}

		for (int i = 0; i < m_options.size(); i++)
		{
			if (m_options[i].id() == option.id())
			{
				logs::logError(std::format("Option with id \"{}\" already exists", option.id()));
				std::exit(1);
			}
		}

		m_options.push_back(option);
		return *this;
	}

	std::string CommandBuilder::generateVersion() const
	{
		return std::format("{} - v{}", m_name, m_version);
	}

	// TODO: support better newlines for terminal width
	std::string CommandBuilder::generateHelp() const
	{
		/* Example help message
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
		std::string helpMessage;

		if (!m_description.empty())
			helpMessage += std::format("{}\n\n", m_description);

		helpMessage += std::format("Usage: {} [OPTIONS]...", m_name);

		std::string arguments = "\n\nArguments:";
		for (const Argument& argument : m_arguments)
		{
			std::string argumentLabel = utils::toUppercase(argument.id());

			helpMessage += (argument.required())
				? std::format(" <{}>", argumentLabel)
				: std::format(" [{}]", argumentLabel);

			if (argument.multiple())
				helpMessage += "...";

			arguments += std::format("\n  {:<25} {}", argumentLabel, argument.description());
		}
		helpMessage += arguments;
		
		std::string options = "\n\nOptions:";
		for (const Option& option : m_options)
		{
			std::string optionLabel = "--" + option.id();

			if (option.hasShortFlag())
				optionLabel += std::format("-{}, ", option.shortFlag());
			else
				optionLabel += "    ";

			if (option.type() == Option::ARGUMENT)
				optionLabel += std::format(" <{}>", utils::toUppercase(option.argument().id()));

			options += std::format("\n  {:<25} {}", optionLabel, option.description());
			
			if (option.type() == Option::ARGUMENT && !option.defaultValue().empty())
				options += std::format(" (default: {})", option.defaultValue());
		}
		helpMessage += options;

		return helpMessage;
	}

	Command CommandBuilder::parse(int argc, const char* argv[])
	{
		// Generate help message at the very end in order to capture everything
		m_options[0].setMessage(generateHelp());

		std::vector<std::string> commandArgs;
		for (int i = 1; i < argc; i++)
			commandArgs.push_back(argv[i]);

		return Command(m_name, m_version, commandArgs, m_arguments, m_options);
	}

}
