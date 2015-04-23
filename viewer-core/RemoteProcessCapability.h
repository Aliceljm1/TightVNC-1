#pragma once

#include "p-client-lib/RemoteProcessRequestSender.h"
#include "p-client-lib/RemoteProcessReplyBuffer.h"
#include "p-client-lib/RemoteProcessMessageProcessor.h"
#include "p-client-lib/RemoteProcessCore.h"

#include "rfb\VendorDefs.h"

#include "ServerMessageListener.h"
#include "CapabilitiesManager.h"

class RemoteProcessCapability : public ServerMessageListener
{
public:
	RemoteProcessCapability(Logger *logger = 0);
	~RemoteProcessCapability();

	void addCapabilities(CapabilitiesManager *capabilities);
	void onServerMessage(UINT32 code, DataInputStream *input);
	void setOutput(RfbOutputGate *output);
	RemoteProcessCore *getCore();

private:
	LogWriter m_logWriter;
	RemoteProcessReplyBuffer m_replyBuffer;
	RemoteProcessRequestSender m_sender;
	RemoteProcessCore m_pCore;
	RemoteProcessMessageProcessor m_msgProcessor;
};

