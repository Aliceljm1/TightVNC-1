#include "RemoteProcessCapability.h"


RemoteProcessCapability::RemoteProcessCapability(Logger *logger, RemoteViewerCore *remoteViewer)
	: m_logWriter(logger),
	m_replyBuffer(&m_logWriter),
	m_sender(&m_logWriter),
	m_pCore(&m_logWriter, &m_sender, &m_replyBuffer, remoteViewer, &m_msgProcessor)
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
	m_msgProcessor.processRfbMessage(input, code);
}

void RemoteProcessCapability::addCapabilities(CapabilitiesManager *capabilities)
{
	// Client-to-Server messages:
	capabilities->addClientMsgCapability(PMessage::PROCESS_LIST_REQUEST,
		VendorDefs::SPOON,
		PMessage::PROCESS_LIST_REQUEST_SIG,
		_T("Process list request"));

	capabilities->addClientMsgCapability(PMessage::PROCESS_ATTACH_REQEST,
		VendorDefs::SPOON,
		PMessage::PROCESS_ATTACH_REQUEST_SIG,
		_T("Process attach request"));

	capabilities->addClientMsgCapability(PMessage::PROCESS_DETACH_REQEST,
		VendorDefs::SPOON,
		PMessage::PROCESS_DETACH_REQUEST_SIG,
		_T("Process detach request"));

	// Server-to-Client messages:
	capabilities->addServerMsgCapability(this,
		PMessage::PROCESS_LIST_REPLY,
		VendorDefs::SPOON,
		PMessage::PROCESS_LIST_REPLY_SIG,
		_T("Process list reply"));

	capabilities->addServerMsgCapability(this,
		PMessage::PROCESS_ATTACH_REPLY,
		VendorDefs::SPOON,
		PMessage::PROCESS_ATTACH_REPLY_SIG,
		_T("Process attach reply"));

	capabilities->addServerMsgCapability(this,
		PMessage::PROCESS_DETACH_REPLY,
		VendorDefs::SPOON,
		PMessage::PROCESS_DETACH_REPLY_SIG,
		_T("Process detach reply"));

	capabilities->addServerMsgCapability(this,
		PMessage::LAST_REQUEST_FAILED_REPLY,
		VendorDefs::SPOON,
		PMessage::LAST_REQUEST_FAILED_REPLY_SIG,
		_T("Last request failed"));
}