#pragma once

#include "io-lib/IOException.h"
#include "io-lib/DataInputStream.h"

#include "util/inttypes.h"
#include "util/ListenerContainer.h"
#include "util/ZLibException.h"

#include "p-common/PMessage.h"

#include "RemoteProcessEventHandler.h"

class RemoteProcessMessageProcessor : public ListenerContainer <RemoteProcessEventHandler * >
{
public:
	RemoteProcessMessageProcessor();
	~RemoteProcessMessageProcessor();

	void processRfbMessage(DataInputStream *input, UINT32 rfbMessage)
		throw (IOException, ZLibException);
};

