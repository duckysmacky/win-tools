#ifndef UTILS_CMD_ARGUMENT_H
#define UTILS_CMD_ARGUMENT_H

#include <string>

namespace cmd
{
	class Argument
	{
	public:
		Argument(const std::string& id);
		~Argument() = default;

		Argument& setDescription(const std::string& description);
		Argument& setRequired(bool value);
		Argument& setMultiple(bool value);

		std::string id() const;
		std::string description() const;
		bool required() const;
		bool multiple() const;

	private:
		std::string m_id;
		std::string m_description;
		bool m_isRequired;
		bool m_isMultiple;
	};
}

#endif // !UTILS_CMD_ARGUMENT_H
