#pragma once

#include "io-lib/DataInputStream.h"

class RemoteProcessEventHandler
{
public:
	RemoteProcessEventHandler();
	~RemoteProcessEventHandler();

	virtual void onProcessListReply(DataInputStream *input) = 0;
	virtual void onProcessAttachReply(DataInputStream *input) = 0;
	virtual void onProcessDetachReply(DataInputStream *input) = 0;
	virtual void onLastRequestFailedReply(DataInputStream *input) = 0;
};

