#pragma once

#include "RemoteProcessOperation.h"

class RemoteProcessOperationEventListener
{
public:
	RemoteProcessOperationEventListener();
	~RemoteProcessOperationEventListener();

	virtual void onStarted(RemoteProcessOperation *operation);
	virtual void onFinished(RemoteProcessOperation *operation);
	virtual void onError(RemoteProcessOperation *operation, const TCHAR *msg);
	virtual void onInfo(RemoteProcessOperation *operation, const TCHAR *msg);
};

