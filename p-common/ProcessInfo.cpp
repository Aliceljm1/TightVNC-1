#include "ProcessInfo.h"


ProcessInfo::ProcessInfo()
{
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
