#include "ircserv.hpp"
#include "colours.hpp"

/*	socket(), getsockopt(), bind(), listen(), accept(), recv()	*/
# include <sys/types.h>
# include <sys/socket.h>

/*	struct sockaddr_in	*/
#include <netinet/in.h>

/*	getprotobyname()	*/
# include <netdb.h>

/*	htons()	*/
#include <arpa/inet.h>

/*	atoi()	*/
#include <cstdlib>

/*	close(), read()	*/
#include <unistd.h>

/*	std::strerror()	*/
#include <cstring>

/*	errno	*/
#include <cerrno>

static void	errorMsg(const std::string &msg)
{
	std::cerr << B_HI_RED << "Error:\n" << RESET << msg << ": " << std::strerror(errno) << std::endl;
}

int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << B_HI_RED << "Error:\n" << RESET
				<< "Correct usage is <./ircserv> <port between 1024 and 65535> <password>"
				<< std::endl;
		return (1);
	}

	std::string	portStr = argv[1];//a checker
	std::string	passwordStr = argv[2];

	struct protoent		*proto = getprotobyname("tcp");
	if (proto == NULL)
	{
		errorMsg("Failed getprotobyname()");
		return (1);
	}
	
	int	socketServer;
	int	socketClient;

	socketServer = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	if (socketServer == -1)
	{
		errorMsg("Failed socket()");
		return (1);
	}
	else
		std::cout << B_HI_GREEN << "Your server has be successfully created!" << RESET << std::endl;

	int	reuse = 1;
	int	sockopt = setsockopt(socketServer, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
	
	if (sockopt == -1)
	{
		errorMsg("Failed getsockopt()");
		return (1);
	}

	struct sockaddr_in	sinServer;

	sinServer.sin_family = AF_INET;
	sinServer.sin_port = htons(atoi(portStr.c_str()));
	sinServer.sin_addr.s_addr = INADDR_ANY;

	if (bind(socketServer, reinterpret_cast<const struct sockaddr *>(&sinServer), sizeof(sinServer)) == -1)
	{
		errorMsg("Failed bind()");
		return (1);
	}
	else if (listen(socketServer, MAX_PENDING_CON) == -1)
	{
		errorMsg("Failed listen()");
		return (1);
	}

	struct sockaddr_in	sinClient;
	unsigned int		sinClientLen = sizeof(sinClient);
	
	sinClient.sin_family = AF_INET;
	sinClient.sin_port = htons(atoi(portStr.c_str()));
	sinClient.sin_addr.s_addr = INADDR_ANY;

	socketClient = accept(socketServer, reinterpret_cast<struct sockaddr *>(&sinClient), &sinClientLen);
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
			return (1);
		}
	}

	std::cout << "Server is shutting down" << std::endl;
	if (close(socketServer) == -1)
	{
		errorMsg("Failed close(socketServer)");
		return (1);
	}
	else if (close(socketClient) == -1)
	{
		errorMsg("Failed closed(socketClient)");
		return (1);
	}
	return (0);
}
