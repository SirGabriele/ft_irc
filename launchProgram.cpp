#include "ircserv.hpp"

/*	std::strncmp()	*/
#include <cstring>

bool	launchProgram(Server &server, int port)
{
	Client	newClient(port);

	try
	{
		server.acceptNewClient(newClient);
	}
	catch (std::exception &exception)
	{
		std::cerr << exception.what() << std::endl;
		return (false);
	}
	while (1)
	{
		fd_set	tempfds = server.getFds();
		int		maxFd = server.getMaxFd();

		if (select(maxFd, &tempfds, NULL, NULL, NULL) < 0)
		{
			std::cerr << "Failed select()" << std::endl;
			return (false);
		}
		for (int i = 0; i < maxFd; i++)
		{
			if (FD_ISSET(i, &tempfds) == 1)
			{
				if (i == server.getSocket()) // new connection
				{
					try
					{
						server.acceptNewClient(newClient);
					}
					catch (std::exception &exception)
					{
						std::cerr << exception.what() << std::endl;
						return (false);
					}
				}
				else // fd is ready to be used
				{
					char    buffer[1024];
					int     howManyBitsRead;
					
					howManyBitsRead = recv(newClient.getSocket(), buffer, sizeof(buffer) - 1, 0);
					buffer[howManyBitsRead - 1] = '\0';
					if (std::strncmp(buffer, "quit", 5) == 0)
						break ;
					else if (howManyBitsRead > 0)
						std::cout << '[' << buffer << ']' << std::endl;
					else if (howManyBitsRead == -1)
					{
						std::cerr << "Failed recv()" << std::endl;
						break ;
					}
					FD_CLR(i, &tempfds);
				}
			}
		}
	}
	return (true);
}
