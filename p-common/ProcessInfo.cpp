#include "ProcessInfo.h"


ProcessInfo::ProcessInfo()
{
}


ProcessInfo::ProcessInfo(const ProcessInfo& other)
{
	m_pid = other.getProcessPid();
	m_processName.setString(other.getProcessName());
}


ProcessInfo::~ProcessInfo()
{
}

void ProcessInfo::setProcessName(const TCHAR *processName)
{
	m_processName.setString(processName);
}


const TCHAR *ProcessInfo::getProcessName() const
{
	return m_processName.getString();
}

void ProcessInfo::setProcessPid(const DWORD pid)
{
	m_pid = pid;
}

const DWORD ProcessInfo::getProcessPid() const
{
	return m_pid;
}
