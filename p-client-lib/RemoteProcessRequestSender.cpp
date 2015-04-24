#include "RemoteProcessRequestSender.h"


RemoteProcessRequestSender::RemoteProcessRequestSender(LogWriter *logWriter)
	: m_logWriter(logWriter), m_output(nullptr)
{
}


void RemoteProcessRequestSender::setOutput(RfbOutputGate *output)
{
	m_output = output;
}


void RemoteProcessRequestSender::sendAttachRemoteProcessRequest(const DWORD pid)
{
	m_logWriter->info(_T("Seding process attach request"));

	{
		AutoLock l(m_output);

		m_output->writeUInt32(PMessage::PROCESS_ATTACH_REQEST);
		m_output->writeUInt32(pid);
		m_output->flush();
	}
}


void RemoteProcessRequestSender::sendDetachRemoteProcessRequest()
{
	m_logWriter->info(_T("Seding process detach request"));

	{
		AutoLock l(m_output);

		m_output->writeUInt32(PMessage::PROCESS_DETACH_REQEST);
		m_output->flush();
	}
}


void RemoteProcessRequestSender::sendListRemoteProcessRequest()
{
	m_logWriter->info(_T("Sending process list request\n"));

	{
		AutoLock al(m_output);

		m_output->writeUInt32(PMessage::PROCESS_LIST_REQUEST);
		m_output->flush();
	}
}