#pragma once

#include "util/inttypes.h"
#include "util/StringStorage.h"

class ProcessInfo
{
public:
	ProcessInfo();
	ProcessInfo(const ProcessInfo& other);
	~ProcessInfo();

	const TCHAR* getProcessName() const;
	const DWORD getProcessPid() const;
	void setProcessName(const TCHAR *processName);
	void setProcessPid(const DWORD pid);
private:
	DWORD m_pid;
	StringStorage m_processName;
};

