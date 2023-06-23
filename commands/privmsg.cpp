/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 08:52:23 by jsauvain          #+#    #+#             */
/*   Updated: 2023/06/23 17:04:53 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_sendMessage(std::stringstream & ss, int indexClient)
{
		std::string	tokentmp;
		char		token[BUFFER_SIZE];

		ss >> token;
		tokentmp = token;
		if (send(_allClients[indexClient].getSocket(), token, tokentmp.length(), \
			MSG_DONTWAIT) == -1)
			std::cout << "Message could not be sent\n";
}

void	Server::_privmsg(std::stringstream & ss)
{
		std::vector<Client>::iterator	it;
		std::string						nickname;

		ss >> nickname;
		for (it = _allClients.begin(); it < _allClients.end(); it++)
		{
			if (it->getNickname().compare(nickname) == 0)
			{
				_sendMessage(ss, it - _allClients.begin());
				return ;
			}
		}
		std::cout << nickname << " not found\n";
}		
