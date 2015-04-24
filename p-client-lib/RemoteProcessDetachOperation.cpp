#include "RemoteProcessDetachOperation.h"


RemoteProcessDetachOperation::RemoteProcessDetachOperation(LogWriter *logWriter)
	: RemoteProcessOperation(logWriter) { }


RemoteProcessDetachOperation::~RemoteProcessDetachOperation() { }


void RemoteProcessDetachOperation::start() throw(IOException)
{
	m_sender->sendDetachRemoteProcessRequest();

	notifyStart();
}


void RemoteProcessDetachOperation::onProcessDetachReply(DataInputStream *input)
{
	notifyFinish();
}


void RemoteProcessDetachOperation::onLastRequestFailedReply(DataInputStream *input)
{
	notifyError(_T("Remote process detach failed"));
	notifyFinish();
}