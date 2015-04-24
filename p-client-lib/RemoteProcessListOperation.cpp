#include "RemoteProcessListOperation.h"


RemoteProcessListOperation::RemoteProcessListOperation(LogWriter *logWriter)
	: RemoteProcessOperation(logWriter), m_isFinished(false), m_isOk(false) { }


void RemoteProcessListOperation::start() {
	m_sender->sendListRemoteProcessRequest();

	this->notifyStart();
}

void RemoteProcessListOperation::onProcessListReply(DataInputStream *input)
{
	m_isFinished = true;
	m_isOk = true;
	notifyFinish();
}

void RemoteProcessListOperation::onLastRequestFailedReply(DataInputStream *input)
{
	m_isFinished = true;
	m_isOk = false;
	notifyError(_T("Error: failed to get the list of remote processes"));
	notifyFinish();
}

BOOL RemoteProcessListOperation::isOk()
{
	return m_isFinished && m_isOk;
}
