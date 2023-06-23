/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 08:52:23 by jsauvain          #+#    #+#             */
/*   Updated: 2023/06/23 11:40:15 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_sendMessage(std::stringstream & ss, int indexClient)
{
		char	token[1024];

		ss >> token;
		if (send(_allClients[indexClient].getSocket(), token, sizeof(token), MSG_DONTWAIT) == -1)
			std::cout << "Message could not be sent\n";
}

void	Server::_privmsg(std::stringstream & ss)
{
		std::vector<Client>::iterator	it;
		std::string						nickname;

		ss >> nickname;
		for (it = _allClients.begin(); it < _allClients.end(); it++)
		{
			std::cout << "username = " << it->getUsername() << std::endl;
			if (it->getNickname().compare(nickname) == 0)
			{
				_sendMessage(ss, it - _allClients.begin());
				return ;
			}
		}
		std::cout << nickname << " not found\n";
}		
