#include "RemoteProcessCapability.h"


RemoteProcessCapability::RemoteProcessCapability(Logger *logger)
	: m_logWriter(logger),
	m_replyBuffer(&m_logWriter),
	m_sender(&m_logWriter),
	m_pCore(&m_logWriter, &m_sender, &m_replyBuffer, &m_msgProcessor)
{
	m_msgProcessor.addListener(&m_replyBuffer);
}

RemoteProcessCapability::~RemoteProcessCapability()
{
}

void RemoteProcessCapability::setOutput(RfbOutputGate *output)
{
	m_sender.setOutput(output);
}

RemoteProcessCore *RemoteProcessCapability::getCore()
{
	return &m_pCore;
}

void RemoteProcessCapability::onServerMessage(UINT32 code, DataInputStream *input)
{
	// propagate message
}

void RemoteProcessCapability::addCapabilities(CapabilitiesManager *capabilities)
{
	// Client-to-Server messages:
	capabilities->addClientMsgCapability(PMessage::PROCESS_LIST_REQUEST,
		VendorDefs::SPOON,
		PMessage::PROCESS_LIST_REQUEST_SIG,
		_T("Process list request"));

	// Server-to-Client messages:
	capabilities->addServerMsgCapability(this,
		PMessage::PROCESS_LIST_REPLY,
		VendorDefs::SPOON,
		PMessage::PROCESS_LIST_REPLY_SIG,
		_T("Process list reply"));

	capabilities->addServerMsgCapability(this,
		PMessage::LAST_REQUEST_FAILED_REPLY,
		VendorDefs::SPOON,
		PMessage::LAST_REQUEST_FAILED_REPLY_SIG,
		_T("Last request failed"));
}