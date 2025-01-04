#ifndef COMMAND_COMMAND_BUILDER_H
#define COMMAND_COMMAND_BUILDER_H

#include <vector>
#include <string>
#include <map>

#include "./Argument.h"
#include "./Option.h"
#include "./Command.h"

namespace cmd
{
	class CommandBuilder
	{
	public:
		CommandBuilder(const std::string& name, const std::string& version);
		~CommandBuilder() = default;

		CommandBuilder& setDescription(const std::string& description);
		CommandBuilder& addArgument(Argument argument);
		CommandBuilder& addOption(Option option);

		Command parse(int argc, const char* argv[]);

	private:
		std::string m_name;
		std::string m_version;
		std::string m_description;

		std::vector<Argument> m_arguments;
		std::vector<Option> m_options;

		std::string generateVersion() const;
		std::string generateHelp() const;
	};
}

#endif // !COMMAND_COMMAND_BUILDER_H