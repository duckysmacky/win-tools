#pragma once

#include "./Argument.hpp"

#include <string>
#include <optional>
#include <set>

namespace cmd
{

	class Option
	{
	public:
		enum Type
		{
			MESSAGE,
			FLAG,
			ARGUMENT
		};

	public:
		Option(const std::string& id);
		~Option() = default;

		Option& setDescription(const std::string& description);
		Option& setArgument(const std::string& defaultValue);
		Option& setMessage(const std::string& message);
		Option& setShortFlag(char flag);
		Option& addConflict(const std::string& id);

		Type type() const;
		std::string id() const;
		std::string description() const;
		std::string defaultValue() const;
		std::string message() const;
		char shortFlag() const;
		bool hasShortFlag() const;
		Argument argument() const;
		std::set<std::string> conflicts() const;

	private:
		Type m_type;
		std::string m_id;
		std::string m_description;
		std::string m_defaultValue;
		std::string m_message;
		std::optional<char> m_shortFlag;
		std::optional<Argument> m_argument;
		std::set<std::string> m_conflictIds;
	};
}
