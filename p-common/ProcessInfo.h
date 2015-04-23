#pragma once

#include "util/inttypes.h"
#include "util/StringStorage.h"

class ProcessInfo
{
public:
	ProcessInfo();
	~ProcessInfo();

	const TCHAR* getProcessName() const;
	void setProcessName(const TCHAR *processName);

private:
	StringStorage m_processName;
};

