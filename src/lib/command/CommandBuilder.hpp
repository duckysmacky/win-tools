#pragma once

#include "./Argument.hpp"
#include "./Option.hpp"
#include "./Command.hpp"

#include <vector>
#include <string>

namespace cmd
{
	class CommandBuilder
	{
	private:
		std::string m_name;
		std::string m_version;
		std::string m_description;

		std::vector<Argument> m_arguments;
		std::vector<Option> m_options;

		std::string generateVersion() const;
		std::string generateHelp() const;

	public:
		CommandBuilder(const std::string& name, const std::string& version);
		~CommandBuilder() = default;

		CommandBuilder& setDescription(const std::string& description);
		CommandBuilder& addArgument(Argument argument);
		CommandBuilder& addOption(Option option);

		Command parse(int argc, const char* argv[]);
	};
}