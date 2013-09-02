#pragma once

namespace Core {

	enum MessageTypes {

		MSG_DEBUG_ENABLED,
		MSG_DEBUG_BREAK,
		MSG_DEBUG_STRING,

		MSG_CONFIG_UPDATED

	};

	struct Message {

		MessageTypes MessageType;
		int MessageParam;
		void* MessageData;

	};

}