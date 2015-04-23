#pragma once

#include <vector>
#include "util/inttypes.h"
#include "io-lib/IOException.h"
#include "log-writer/LogWriter.h"
#include "p-common/ProcessInfo.h"
#include "RemoteProcessRequestSender.h"
#include "RemoteProcessOperation.h"
#include "RemoteProcessOperationEventListener.h"
#include "RemoteProcessEventHandler.h"
#include "RemoteProcessListOperation.h"

using std::vector;

class RemoteProcessCore : public RemoteProcessOperationEventListener
{
public:
	RemoteProcessCore(LogWriter *logWriter,
		RemoteProcessRequestSender *sender,
		RemoteProcessReplyBuffer *replyBuffer,
		ListenerContainer<RemoteProcessEventHandler *> *pListeners);
	~RemoteProcessCore();

	vector <ProcessInfo> *getRemoteProcessList();
	void remoteProcessListOperation();
	void terminateCurrentOperation();

protected:
	virtual void onStarted(RemoteProcessOperation *operation);
	virtual void onFinished(RemoteProcessOperation *operation);
	virtual void onError(RemoteProcessOperation *operation, const TCHAR *msg);
	virtual void onInfo(RemoteProcessOperation *operation, const TCHAR *msg);

private:
	void executeOperation(RemoteProcessOperation *operation) throw(IOException);

	LogWriter *m_logWriter;
	RemoteProcessRequestSender *m_sender;
	RemoteProcessReplyBuffer *m_replyBuffer;
	ListenerContainer<RemoteProcessEventHandler *> *m_remoteProcessListeners;

	enum class State {
		Idle,
		List,
		Attach,
		Detach
	};

	State m_state;
	RemoteProcessOperation *m_currentOperation;
	vector<ProcessInfo> m_remoteProcessInfo;
};
