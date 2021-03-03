#pragma once

#include <string>
#include <queue>
#include "network_packet.hpp"

namespace dragonblocks
{
	 		std::queue<NetworkPacket> in_packets;
		std::queue<NetworkPacket> out_packets;
}
