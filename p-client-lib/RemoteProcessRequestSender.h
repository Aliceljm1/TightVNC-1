#pragma once

#include "util/inttypes.h"
#include "io-lib/IOException.h"
#include "log-writer/LogWriter.h"
#include "thread/AutoLock.h"
#include "p-common/PMessage.h"
#include "network/RfbOutputGate.h"

class RemoteProcessRequestSender
{
public:
	RemoteProcessRequestSender(LogWriter *m_logWriter);

	void setOutput(RfbOutputGate *output);

	void sendListRemoteProcessRequest() throw(IOException);
	void sendAttachRemoteProcessRequest(const DWORD pid) throw(IOException);
	void sendDetachRemoteProcessRequest() throw(IOException);
private:
	RfbOutputGate *m_output;
	LogWriter *m_logWriter;
};

