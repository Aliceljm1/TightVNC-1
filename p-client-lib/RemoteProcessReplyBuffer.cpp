#include "RemoteProcessReplyBuffer.h"


RemoteProcessReplyBuffer::RemoteProcessReplyBuffer(LogWriter *logWriter)
	: m_logWriter(logWriter), m_processInfoCount(0), m_processInfo(nullptr) { }


RemoteProcessReplyBuffer::~RemoteProcessReplyBuffer()
{
	if (m_processInfoCount > 0) {
		delete[] m_processInfo;
	}
}


UINT32 RemoteProcessReplyBuffer::getProcessInfoCount()
{
	return m_processInfoCount;
}

ProcessInfo *RemoteProcessReplyBuffer::getProcessInfo()
{
	return m_processInfo;
}


void RemoteProcessReplyBuffer::onLastRequestFailedReply(DataInputStream *input)
{
	input->readUTF8(&m_lastErrorMessage);

	m_logWriter->info(_T("Received last request failed reply:\n")
		_T("\terror message: %s\n"),
		m_lastErrorMessage.getString());
}


void RemoteProcessReplyBuffer::onProcessListReply(DataInputStream *input)
{
	if (m_processInfo != 0) {
		delete[] m_processInfo;
		m_processInfoCount = 0;
	}

	m_processInfoCount = input->readUInt32();
	if (m_processInfoCount != 0) {
		m_processInfo = new ProcessInfo[m_processInfoCount];
	}

	for (auto i = 0; i < m_processInfoCount; ++i) {
		ProcessInfo *processInfo = &m_processInfo[i];

		StringStorage t;
		input->readUTF8(&t);

		processInfo->setProcessName(t.getString());
	}

	m_logWriter->info(_T("Received file list reply: \n")
		_T("\t process count = %d\n"),
		m_processInfoCount);
}


void RemoteProcessReplyBuffer::onProcessAttachReply(DataInputStream *input) { }

void RemoteProcessReplyBuffer::onProcessDetachReply(DataInputStream *input) { }