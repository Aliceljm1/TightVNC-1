#pragma once

#include "io-lib\IOException.h"
#include "log-writer\LogWriter.h"
#include "RemoteProcessOperation.h"

class RemoteProcessDetachOperation : public RemoteProcessOperation
{
public:
	RemoteProcessDetachOperation(LogWriter *logWriter);
	~RemoteProcessDetachOperation();

	virtual void start() throw(IOException);

	virtual void onProcessDetachReply(DataInputStream *input);
	virtual void onLastRequestFailedReply(DataInputStream *input);
};

