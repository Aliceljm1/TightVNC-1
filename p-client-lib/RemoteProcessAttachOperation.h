#pragma once

#include "io-lib\IOException.h"
#include "log-writer\LogWriter.h"
#include "RemoteProcessOperation.h"

class RemoteProcessAttachOperation : public RemoteProcessOperation
{
public:
	RemoteProcessAttachOperation(LogWriter *logWriter, DWORD pid);
	~RemoteProcessAttachOperation();

	virtual void start() throw(IOException);

	virtual void onProcessAttachReply(DataInputStream *input);
	virtual void onLastRequestFailedReply(DataInputStream *input);

private:
	DWORD m_pid;
};

