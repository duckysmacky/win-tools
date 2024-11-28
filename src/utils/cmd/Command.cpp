#include "Command.h"

namespace utils
{
	Command::Command(const std::string& name, const std::string& version)
		: m_name(name), m_version(version)
	{
		addOption(CommandOption("HELP", CommandOption::MESSAGE)
			.setDescription("Shows help information about this command")
			.setShortFlag("h")
			.setLongFlag("help")
		);
		addOption(CommandOption("VERSION", CommandOption::MESSAGE)
			.setDescription("Shows version information for this command")
			.setShortFlag("V")
			.setLongFlag("version")
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

}
