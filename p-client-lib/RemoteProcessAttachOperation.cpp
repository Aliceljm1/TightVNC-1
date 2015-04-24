#include "RemoteProcessAttachOperation.h"


RemoteProcessAttachOperation::RemoteProcessAttachOperation(LogWriter *logWriter, DWORD pid)
	: RemoteProcessOperation(logWriter), m_pid(pid) { }


RemoteProcessAttachOperation::~RemoteProcessAttachOperation() { }


void RemoteProcessAttachOperation::start()
{
	m_sender->sendAttachRemoteProcessRequest(m_pid);

	notifyStart();
}


void RemoteProcessAttachOperation::onProcessAttachReply(DataInputStream *input)
{
	notifyFinish();
}


void RemoteProcessAttachOperation::onLastRequestFailedReply(DataInputStream *input)
{
	notifyError(_T("Error: failed to attach to the process"));
	notifyFinish();
}