#include "RemoteProcessMessageProcessor.h"


RemoteProcessMessageProcessor::RemoteProcessMessageProcessor()
{
}


RemoteProcessMessageProcessor::~RemoteProcessMessageProcessor()
{
}


void RemoteProcessMessageProcessor::processRfbMessage(DataInputStream *input,
	UINT32 rfbMessage)
	throw (IOException, ZLibException)
{
	AutoLock al(&m_listeners);

	for (auto listener : m_listeners) {
		switch (rfbMessage) {
		case PMessage::LAST_REQUEST_FAILED_REPLY:
			listener->onLastRequestFailedReply(input);
			break;
		case PMessage::PROCESS_ATTACH_REPLY:
			listener->onProcessAttachReply(input);
			break;
		case PMessage::PROCESS_DETACH_REPLY:
			listener->onProcessDetachReply(input);
			break;
		case PMessage::PROCESS_LIST_REPLY:
			listener->onProcessListReply(input);
			break;
		}
	}
}