#include "Server.hpp"

/*	std::strncmp()	*/
#include <cstring>

bool	Server::_receiveData(int socket)
{
	if (socket == this->_socket) // new connection
	{
		if (_acceptNewClient() == false)
			return (false);
	}
	else // fd is ready to be used
	{
		char    buffer[BUFFER_SIZE];
		int     howManyBitsRead;
		
		std::memset(buffer, '\0', sizeof(buffer));
		howManyBitsRead = recv(socket, buffer, BUFFER_SIZE, 0);
		if (howManyBitsRead == -1)
		{
			std::cerr << "Failed recv()" << std::endl;
			return (false) ;
		}
		else if (std::strncmp(buffer, "quit", 5) == 0)
			_disconnectClient(socket);
		else if (howManyBitsRead > 0)
		{
			if (_processInput(socket, buffer) == false)
				return (false);
		}
	}
	return (true);
}

bool	Server::run(void)
{
	while (g_signal == 0)
	{
		fd_set	readfds = _readfds;
		fd_set	writefds = _writefds;

		if (select(_maxFd + 1, &readfds, &writefds, NULL, NULL) < 0)
		{
			if (g_signal != 130)
				std::cerr << "Failed select()" << std::endl;
			return (false);
		}
		for (int i = 0; i <_maxFd + 1; i++)
		{
			if (FD_ISSET(i, &readfds) == 1)
			{
				if (_receiveData(i) == false)
					return (false);
			}
		}
	}
	return (true);
}
