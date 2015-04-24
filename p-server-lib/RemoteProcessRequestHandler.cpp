#include "RemoteProcessRequestHandler.h"


BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lparam);

RemoteProcessRequestHandler::RemoteProcessRequestHandler(RfbCodeRegistrator *registrator,
	RfbOutputGate *output,
	LogWriter *log)
	: m_log(log), m_output(output), m_registrator(registrator)
{
	registrator->addClToSrvCap(PMessage::PROCESS_LIST_REQUEST, VendorDefs::SPOON, PMessage::PROCESS_LIST_REQUEST_SIG);
	registrator->addClToSrvCap(PMessage::PROCESS_ATTACH_REQEST, VendorDefs::SPOON, PMessage::PROCESS_ATTACH_REQUEST_SIG);
	registrator->addClToSrvCap(PMessage::PROCESS_DETACH_REQEST, VendorDefs::SPOON, PMessage::PROCESS_DETACH_REQUEST_SIG);

	registrator->addClToSrvCap(PMessage::PROCESS_LIST_REPLY, VendorDefs::SPOON, PMessage::PROCESS_LIST_REPLY_SIG);
	registrator->addClToSrvCap(PMessage::PROCESS_ATTACH_REPLY, VendorDefs::SPOON, PMessage::PROCESS_ATTACH_REPLY_SIG);
	registrator->addClToSrvCap(PMessage::PROCESS_DETACH_REPLY, VendorDefs::SPOON, PMessage::PROCESS_DETACH_REPLY_SIG);
	registrator->addClToSrvCap(PMessage::LAST_REQUEST_FAILED_REPLY, VendorDefs::SPOON, PMessage::LAST_REQUEST_FAILED_REPLY_SIG);

	registrator->regCode(PMessage::PROCESS_LIST_REQUEST, this);
	registrator->regCode(PMessage::PROCESS_ATTACH_REQEST, this);
	registrator->regCode(PMessage::PROCESS_DETACH_REQEST, this);
}


RemoteProcessRequestHandler::~RemoteProcessRequestHandler()
{
}


void RemoteProcessRequestHandler::onRequest(UINT32 reqCode, RfbInputGate *backGate)
{
	try {
		switch (reqCode) {
		case PMessage::PROCESS_LIST_REQUEST:
			processListRequested(backGate);
			break;
		case PMessage::PROCESS_ATTACH_REQEST:
			processAttachRequested(backGate);
			break;
		case PMessage::PROCESS_DETACH_REQEST:
			processDetachRequested(backGate);
			break;
		}
	}
	catch (Exception &someEx) {
		lastRequestFailed(backGate, someEx.getMessage());
	}
}


void RemoteProcessRequestHandler::processListRequested(RfbInputGate *backGate) {
	m_log->message(_T("Process list requested"));

	ProcessList processList;
	auto processes = processList.getProcesses();

	{
		AutoLock l(m_output);

		m_output->writeUInt32(PMessage::PROCESS_LIST_REPLY);
		m_output->writeUInt32(processes->size());

		for (auto p : *processes)
		{
			m_output->writeInt32(p.getProcessPid());
			m_output->writeUTF8(p.getProcessName());
		}

		m_output->flush();
	}
}


void RemoteProcessRequestHandler::processAttachRequested(RfbInputGate *gate)
{
	m_log->message(_T("Process attach requested"));

	DWORD pid = gate->readUInt32();

	{
		AutoLock l(m_output);

		m_output->writeUInt32(PMessage::PROCESS_ATTACH_REPLY);
		m_output->flush();
	}
}


void RemoteProcessRequestHandler::processDetachRequested(RfbInputGate *gate)
{
	m_log->message(_T("Process detach requested"));

	{
		AutoLock l(m_output);

		m_output->writeUInt32(PMessage::PROCESS_DETACH_REPLY);
		m_output->flush();
	}
}


void RemoteProcessRequestHandler::lastRequestFailed(RfbInputGate *backGate, const TCHAR *msg) {
	m_log->error(_T("last request failed: \"%s\""), msg);

	{
		AutoLock l(m_output);

		m_output->writeInt32(PMessage::LAST_REQUEST_FAILED_REPLY);
		m_output->writeUTF8(msg);
		m_output->flush();
	}
}


