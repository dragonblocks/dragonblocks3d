#pragma once

#include <string>
#include <netinet/in.h>

#define DRAGONBLOCKS_UPD_SOCKET_PACKAGE_SIZE 1024

namespace dragonblocks
{
	class UDPSocket
	{
		public:
		class Address
		{
			public:
			struct sockaddr_in address;
			int length;
			
			Address() = default;
			Address(const std::string &, int);
		};
		
		void connect();
		void bind();
		void close();
		void send(const std::string &, Address * = nullptr);			// server specifies address 
		std::string recv(Address * = nullptr);							// server provides a buffer for the address
		
		UDPSocket(const std::string &, int);

		private:		
		int sockfd;
		Address address;												// for client, this is the address of the server; for server it is the own address.
	}; 
}
