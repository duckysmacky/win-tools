#ifndef UTILS_CMD_COMMAND_ARGUMENT_H
#define UTILS_CMD_COMMAND_ARGUMENT_H

#include <string>
#include <variant>

namespace utils
{

	class CommandArgument
	{
	public:
		typedef std::variant<std::string, int, bool> ValueVariant;
		
		enum Type
		{
			STRING,
			INT,
			BOOL
		};

	public:
		CommandArgument(const std::string& id, Type type);
		~CommandArgument() = default;

		CommandArgument& setDescription(const std::string& description);
		CommandArgument& isRequired(bool value);
		CommandArgument& isMultiple(bool value);

		std::string id() const;
		std::string description() const;
		Type type() const;
		bool required() const;
		bool multiple() const;

	private:
		std::string m_id;
		std::string m_description;
		Type m_type;
		ValueVariant m_value;
		bool m_isRequired;
		bool m_isMultiple;
	};
}

#endif // !UTILS_CMD_COMMAND_ARGUMENT_H
