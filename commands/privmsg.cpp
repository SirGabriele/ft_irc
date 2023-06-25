/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 08:52:23 by jsauvain          #+#    #+#             */
/*   Updated: 2023/06/25 13:50:30 by jsauvain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

void	Server::_sendMessage(Client & client, int indexDestClient)
{
		std::string	message;
		size_t		pos = 0;
		
		for (int i = 0; i < 2; i++)
		{
			pos = client.getInput().find_first_of(" 	", pos);
			if (pos == std::string::npos)
				return ;
			pos = client.getInput().find_first_not_of(" 	", pos);
		}
		message = client.getInput().substr(pos);
		//Mettre une longeur de message max ?
		if (send(_allClients[indexDestClient].getSocket(), message.c_str(), \
			message.length(), MSG_DONTWAIT) == -1)
			std::cout << "Message could not be sent\n";
}

void	Server::_privmsg(std::stringstream & ss, Client & client)
{
		std::vector<Client>::iterator	it;
		std::string						nickname;

		if (client.getNickname().empty() == true)
			std::cout << "You have to set a nickname\n";
		else if (client.getUsername().empty() == true)
			std::cout << "You have to set a username\n";
		else
		{
			ss >> nickname;
			for (it = _allClients.begin(); it < _allClients.end(); it++)
			{
				if (it->getNickname().compare(nickname) == 0)
				{
					_sendMessage(client, it - _allClients.begin());
					return ;
				}
			}
			if (nickname.empty() == false)
				std::cout << "user '" << nickname << "' not found\n";
			else
				std::cout << "You must specify who the message is adressed to\n";
		}
}		
