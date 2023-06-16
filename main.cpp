#include "Server.hpp"

/*	atoi()	*/
#include <cstdlib>

int	isPortValid(std::string &portStr)
{
	if (portStr.length() > 5)
		return (-1);
	for (std::string::size_type i = 0; i < portStr.length(); i++)
	{
		if (isdigit(portStr[i]) == 0)
			return (-1);
	}

	int	portInt = atoi(portStr.c_str());

	if (portInt > 65535)
		return (-1);
	return (portInt);
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << B_HI_RED << "Error:\n" << RESET
				<< "Correct usage is <./ircserv> <port> <password>"
				<< std::endl;
		return (1);
	}

	std::string	portStr = argv[1];
	std::string	passwordStr = argv[2];	//----------------------------------------a verifier?
	int	portInt = isPortValid(portStr);

	if (portInt < 1024)
	{
		std::cerr << B_HI_RED << "Error:\n" << RESET << "<port> must be an numeric value between 1024 and 65535" << std::endl;
		return (1);
	}

	try
	{
		Server	server(portInt);
	}
	catch (std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
		return (1);
	}

/*	
	struct sockaddr_in	sinClient;
	unsigned int		sinClientLen = sizeof(sinClient);
	
	sinClient.sin_family = AF_INET;
	sinClient.sin_port = htons(atoi(portStr.c_str()));
	sinClient.sin_addr.s_addr = INADDR_ANY;

	socketClient = accept(server.getSocket(), reinterpret_cast<struct sockaddr *>(&sinClient), &sinClientLen);
	if (socketClient == -1)
	{
		errorMsg("Failed accept()");
		return (1);
	}
	while (1)
	{
		char	buffer[10];
		int		howManyBitsRead;

		howManyBitsRead = recv(socketClient, buffer, sizeof(buffer) - 1, 0);
		buffer[howManyBitsRead - 1] = '\0';
		if (std::strncmp(buffer, "quit", 5) == 0)
			break ;
		else if (howManyBitsRead > 0)
			std::cout << '[' << buffer << ']' << std::endl;
		else if (howManyBitsRead == -1)
		{
			errorMsg("Failed recv()");
			break ;
		}
	}

	std::cout << "Server is shutting down" << std::endl;
	if (close(server.getSocket()) == -1)
	{
		errorMsg("Failed close(socketServer)");
		return (1);
	}
	else if (close(socketClient) == -1)
	{
		errorMsg("Failed closed(socketClient)");
		return (1);
	}
*/
	return (0);
}
