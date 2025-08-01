#pragma once

#include "./Argument.hpp"
#include "./Option.hpp"

#include <string>
#include <vector>
#include <map>
#include <optional>

namespace cmd
{
	class Command
	{
	private:
		std::string m_name;
		std::string m_version;

		std::vector<std::string> m_commandArgs;
		std::vector<Argument> m_arguments;
		std::vector<Option> m_options;
		
		int m_nextArgument;

		std::map<std::string, std::string> m_singleValues;
		std::map<std::string, std::vector<std::string>> m_multipleValues;
		std::map<std::string, bool> m_flagValues;

	public:
		Command(
			const std::string& name,
			const std::string& version,
			const std::vector<std::string>& commandArgs,
			const std::vector<Argument>& arguments,
			const std::vector<Option>& options
		);
		~Command() = default;

		bool hasValue(const std::string& id) const;
		bool hasMultiple(const std::string& id) const;

		std::optional<std::string> getValue(const std::string& id) const;
		std::optional<std::vector<std::string>> getMultiple(const std::string& id) const;
		bool getFlag(const std::string& id) const;

		std::string name() const;
		std::string version() const;

	private:
		void handleArgument(int i);
		void handleShortFlag(int i);
		void handleLongFlag(int i);
		void handleOption(const Option& option, int i);

		Option findOption(const std::string& longFlag);
		Option findOption(char shortFlag);
	};
}
