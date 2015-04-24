#pragma once

#include "io-lib/IOException.h"
#include "log-writer/LogWriter.h"
#include "util/ListenerContainer.h"
#include "RemoteProcessRequestSender.h"
#include "RemoteProcessReplyBuffer.h"

class RemoteProcessOperationEventListener;

class RemoteProcessOperation : 
	public RemoteProcessEventHandler,
	public ListenerContainer <RemoteProcessOperationEventListener *>
{
public:
	RemoteProcessOperation(LogWriter *logWriter);
	~RemoteProcessOperation();

	virtual void onProcessListReply(DataInputStream *input);
	virtual void onProcessAttachReply(DataInputStream *input);
	virtual void onProcessDetachReply(DataInputStream *input);
	virtual void onLastRequestFailedReply(DataInputStream *input);

	virtual void start() throw(IOException) = 0;
	void setRequestSender(RemoteProcessRequestSender *requestSender);
	void setReplyBuffer(RemoteProcessReplyBuffer *replyBuffer);
protected:
	LogWriter *m_logWriter;
	RemoteProcessRequestSender *m_sender;
	RemoteProcessReplyBuffer *m_replyBuffer;

	void notifyStart();
	void notifyFinish();
	void notifyInfo(const TCHAR *msg);
	void notifyError(const TCHAR *msg);
};

