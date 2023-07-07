#include <iostream>
#include <cstdlib>

std::string	passwordGenerator(void)
{
	std::string	password;
	std::string	length;
	int			len;

	std::cout << "Choose your password's length: ";
	std::getline(std::cin, length);
	if (length.find_first_not_of("0123456789") != std::string::npos)
		std::cout << "You must choose a positive integer\n";
	else
	{
		len = std::atoi(length.c_str());
		for (int i = 0; i < len; i++)
			password += (std::rand() % 94 + 32);
		std::cout << std::endl << "Here is your new password: " << password << std::endl;
	}
	return (password);
}
