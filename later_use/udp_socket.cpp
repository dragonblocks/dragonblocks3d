#include <stdexcept>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "udp_socket.hpp" 

#define PACKSIZE DRAGONBLOCKS_UPD_SOCKET_PACKAGE_SIZE

using namespace std;
using namespace dragonblocks;

UDPSocket::Address::Address(const string &adr, int port)
{
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	inet_pton(AF_INET, adr.c_str(), &address.sin_addr);
}
void UDPSocket::connect()
{
	if (::connect(sockfd, (struct sockaddr *)&address.address, address.length) < 0)
		throw runtime_error("Connection failed");
}

void UDPSocket::bind()
{
	if (::bind(sockfd, (struct sockaddr *)&address.address, address.length) < 0)
		throw runtime_error("Bind failed");
}

void UDPSocket::close()
{
	::close(sockfd);
}

void UDPSocket::send(const std::string &str, Address *addr)
{
	if (! addr) {
		addr = &address;
	}
	sendto(sockfd, str.c_str(), min((int)str.size(), PACKSIZE), MSG_CONFIRM, (struct sockaddr *)&addr->address, addr->length);  
}

string UDPSocket::recv(Address *addr)
{
	if (! addr) {
		addr = &address;
	}
	char buffer[PACKSIZE + 1] = {0};									// include \0 at the end
	recvfrom(sockfd, buffer, PACKSIZE, MSG_WAITALL, (struct sockaddr *)&addr->address, (socklen_t *)&addr->length);
	return buffer;
}

UDPSocket::UDPSocket(const string &adr, int port) : address(adr, port)
{
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
}
