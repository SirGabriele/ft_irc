#include "ircserv.hpp"

/*	std::strncmp()	*/
#include <cstring>

bool	launchProgram(Server &server)
{
	while (1)
	{
		fd_set	readfds = server.getReadFds();
		fd_set	writefds = server.getWriteFds();
		fd_set	exceptfds = server.getExceptFds();

		if (select(server.getMaxFd() + 1, &readfds, &writefds, &exceptfds, NULL) < 0)
		{
			std::cerr << "Failed select()" << std::endl;
			return (false);
		}
		for (int i = 0; i < server.getMaxFd() + 1; i++)
		{
			if (FD_ISSET(i, &readfds) == 1)
			{
				if (i == server.getSocket()) // new connection
				{
					try
					{
						server.acceptNewClient();
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
					
					howManyBitsRead = recv(i, buffer, sizeof(buffer) - 1, 0);
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
				}
			}
		}
	}
	return (true);
}
