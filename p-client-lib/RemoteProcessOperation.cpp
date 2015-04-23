#include "RemoteProcessOperationEventListener.h"
#include "RemoteProcessOperation.h"


RemoteProcessOperation::RemoteProcessOperation(LogWriter *logWriter)
	: m_logWriter(logWriter), m_sender(0), m_replyBuffer(0) { }


RemoteProcessOperation::~RemoteProcessOperation()
{
}


void RemoteProcessOperation::setRequestSender(RemoteProcessRequestSender *requestSender) {
	m_sender = requestSender;
}

void RemoteProcessOperation::setReplyBuffer(RemoteProcessReplyBuffer *replyBuffer) {
	m_replyBuffer = replyBuffer;
}

void RemoteProcessOperation::notifyStart()
{
	AutoLock al(&m_listeners);

	for (auto listener : m_listeners)
	{
		listener->onStarted(this);
	}
}

void RemoteProcessOperation::notifyFinish()
{
	AutoLock al(&m_listeners);

	for (auto listener : m_listeners)
	{
		listener->onFinished(this);
	}
}

void RemoteProcessOperation::notifyError(const TCHAR *message)
{
	m_logWriter->message(_T("%s\n"), message);

	AutoLock al(&m_listeners);

	for (auto listener : m_listeners)
	{
		listener->onError(this, message);
	}
}

void RemoteProcessOperation::notifyInfo(const TCHAR *message)
{
	m_logWriter->message(_T("%s\n"), message);

	AutoLock al(&m_listeners);

	for (auto listener : m_listeners)
	{
		listener->onInfo(this, message);
	}
}
