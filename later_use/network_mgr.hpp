#pragma once

#include <map>
#include <set>
#include <string>
#include <queue>
#include "udp_socket.hpp"

namespace dragonblocks
{
	class NetworkMgr
	{
		public:
		class IPeer
		{
			public:
			UDPSocket::Address *address;
			NetworkMgr *network_mgr;
		};
		
		class INamespace
		{
			public:
			virtual void handle(Packet *);
		};
		
		UDPSocket *socket;
		std::queue<Packet *> out_queue;
		std::set<IPeer *> peers_set;
		std::map<Address *, IPeer *> peers;
		void sendPacket(Packet *);
		void disconnectPeer(IPeer *);
		std::map<std::string, INamespace *> namespaces;
	};
}
