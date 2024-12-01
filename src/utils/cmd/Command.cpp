#include "Command.h"

#include <format>

#include "../string-utils.h"

namespace utils
{
	Command::Command(const std::string& name, const std::string& version)
		: m_name(name), m_version(version)
	{
		addOption(CommandOption("HELP", CommandOption::MESSAGE)
			.setDescription("Shows help information about this command")
			.setShortFlag("h")
		);
		addOption(CommandOption("VERSION", CommandOption::MESSAGE)
			.setDescription("Shows version information for this command")
			.setShortFlag("V")
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

}
