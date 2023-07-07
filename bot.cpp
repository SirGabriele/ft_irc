#include <iostream>
#include <sys/socket.h>
#include <netdb.h>
#include <cstdlib>
#include <unistd.h>

std::string	passwordGenerator(void);

bool	isPortNumeric(std::string port)
{
	size_t	pos;

	pos = port.find_first_not_of("0123456789");
	if (pos != std::string::npos)
	{
		if (pos == 0 && port[0] == '-' && port.find_first_not_of("0123456789", pos) == std::string::npos)
			std::cout << "Error: <port> must be a positive integer\n";
		else
			std::cout << "Error: <port> must be numeric\n";
		return (false);
	}
	return (true);
}

int	createSocket(void)
{
	struct protoent	*proto;
	int				socketfd;
   	
	proto = getprotobyname("tcp");
	if (!proto)
	{
		std::cout << "Error: cannot get protocol's structure\n";
		return (-1);
	}
	socketfd = socket(AF_INET, SOCK_STREAM, proto->p_proto);
	return (socketfd);
}

int	ft_strlen(char *buf)
{
	int i = 0;

	while (buf[i])
		i++;
	return (i);
}

void	serverCommunication(int sockfd)
{
	std::string	password;
	char		buf[1024];
	int			ret;

	while (1)
	{
		ret = read(sockfd, buf, 1024);
		if (ret == -1)
		{
			std::cout << "Error: cannot read socket\n";
			continue ;
		}
		password = passwordGenerator();
		ret = write(sockfd, password.c_str(), password.length());
		if (ret == -1)
		if (ret == -1)
		{
			std::cout << "Error: cannot write on socket\n";
			continue ;
		}
	}
}

void	connectToServer(int port)
{
	int					sockfd;
	struct sockaddr_in	serveraddr;

	sockfd = createSocket();
	if (sockfd == -1)
		return ;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);
	serveraddr.sin_addr.s_addr = INADDR_ANY;
	if (connect(sockfd, reinterpret_cast<struct sockaddr *>(&serveraddr), sizeof(serveraddr)) == -1)
		std::cout << "Error connecting to server\n";
	else
		serverCommunication(sockfd);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		std::cout << "Usage: ./botIrc <port>\n";
	else
	{
		if (isPortNumeric(argv[1]) == true)
			connectToServer(std::atoi(argv[1]));
	}
}
