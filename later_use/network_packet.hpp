#pragma once

#include <sstream>

namespace dragonblocks
{
	class Connection;
	
	class NetworkPacket
	{
		public:
		enum Type
		{
			INVALID,
			TOSERVER_HELLO,
			TOCLIENT_HELLO,
			TOSERVER_BYE,
			TOCLIENT_BYE,
			TYPE_COUNT,
		};
		
		std::stringstream content;

		NetworkPacket() = default;
		NetworkPacket(const Type &);
		NetworkPacket(const NetworkPacket &) = default;
		
		private:
		Type type = INVALID;
	};
} 
