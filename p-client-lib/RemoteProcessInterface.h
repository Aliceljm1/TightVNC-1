#pragma once

#include "io-lib/IOException.h"

class RemoteProcessInterface
{
public:
	RemoteProcessInterface();
	~RemoteProcessInterface();

	virtual void setIdleState() = 0;
	virtual void onRefreshProcessList() = 0;
	virtual void onAttachProcess(DWORD pid) = 0;
	virtual void onDetachProcess() = 0;
	virtual void raise(Exception &ex) = 0;

	enum class State {
		Idle,
		List,
		Attach,
		Detach
	};

	virtual void onOpStarted() = 0;
	virtual void onOpFinished(State state, BOOL result) = 0;
};

