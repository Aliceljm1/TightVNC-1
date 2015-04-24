#pragma once

#include "io-lib/IOException.h"
#include "log-writer/LogWriter.h"
#include "RemoteProcessRequestSender.h"
#include "RemoteProcessOperation.h"

class RemoteProcessListOperation : public RemoteProcessOperation
{
public:
	RemoteProcessListOperation(LogWriter *logWriter);

	virtual void start() throw(IOException);

	virtual void onProcessListReply(DataInputStream *input);
	virtual void onLastRequestFailedReply(DataInputStream *input);

	BOOL isOk();
private:
	BOOL m_isOk;
	BOOL m_isFinished;
};

