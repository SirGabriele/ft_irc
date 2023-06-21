#include "ircserv.hpp"

bool	isInputFull(const std::string &input)
{
	for (std::string::size_type i = 0; i < input.length(); i++)
	{
		if (input[i] == '\n')
			return (true);
	}
	return (false);
}
