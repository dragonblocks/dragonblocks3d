#include <stdexcept>
#include "connection.hpp"

using namespace std;
using namespace dragonblocks;

void Connection::setAddress(const string &addr)
{
	if(inet_pton(AF_INET, addr.c_str(), &address.sin_addr) <= 0)
		throw runtime_error(string("Invalid address: ") + addr);
}


