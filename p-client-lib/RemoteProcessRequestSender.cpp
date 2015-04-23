#include "RemoteProcessRequestSender.h"


RemoteProcessRequestSender::RemoteProcessRequestSender(LogWriter *logWriter)
	: m_logWriter(logWriter), m_output(nullptr)
{
}


void RemoteProcessRequestSender::setOutput(RfbOutputGate *output)
{
	m_output = output;
}


void RemoteProcessRequestSender::sendAttachRemoteProcessRequest(const TCHAR *processName) { }


void RemoteProcessRequestSender::sendDetachRemoteProcessRequest(const TCHAR *processName) { }


void RemoteProcessRequestSender::sendListRemoteProcessRequest()
{
	AutoLock al(m_output);

	UINT32 messageId = PMessage::PROCESS_LIST_REQUEST;

	m_logWriter->info(_T("Sending process list request\n"));

	m_output->writeUInt32(messageId);
	m_output->flush();
}