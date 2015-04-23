#pragma once

#include "io-lib/DataInputStream.h"
#include "p-common/ProcessInfo.h"
#include "log-writer/LogWriter.h"
#include "RemoteProcessEventHandler.h"

class RemoteProcessReplyBuffer : public RemoteProcessEventHandler
{
public:
	RemoteProcessReplyBuffer(LogWriter *logWriter);
	~RemoteProcessReplyBuffer();

	virtual void onLastRequestFailedReply(DataInputStream *input) throw(IOException);
	virtual void onProcessListReply(DataInputStream *input) throw(IOException);
	virtual void onProcessAttachReply(DataInputStream *input) throw(IOException);
	virtual void onProcessDetachReply(DataInputStream *input) throw(IOException);

	UINT32 getProcessInfoCount();
	ProcessInfo *getProcessInfo();
protected:
	LogWriter *m_logWriter;

	UINT32 m_processInfoCount;
	ProcessInfo *m_processInfo;

	StringStorage m_lastErrorMessage;
};

