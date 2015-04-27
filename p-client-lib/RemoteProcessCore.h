#pragma once

#include <vector>
#include "util/inttypes.h"
#include "io-lib/IOException.h"
#include "log-writer/LogWriter.h"
#include "p-client-lib/RemoteProcessCore.h"
#include "p-common/ProcessInfo.h"
#include "RemoteProcessRequestSender.h"
#include "RemoteProcessOperation.h"
#include "RemoteProcessOperationEventListener.h"
#include "RemoteProcessEventHandler.h"
#include "RemoteProcessInterface.h"
#include "RemoteProcessListOperation.h"
#include "RemoteProcessAttachOperation.h"
#include "RemoteProcessDetachOperation.h"
#include "viewer-core/RemoteViewerCore.h"

using std::vector;

class RemoteProcessCore : public RemoteProcessOperationEventListener
{
public:
	RemoteProcessCore(LogWriter *logWriter,
		RemoteProcessRequestSender *sender,
		RemoteProcessReplyBuffer *replyBuffer,
		RemoteViewerCore *remoteViewer,
		ListenerContainer<RemoteProcessEventHandler *> *pListeners);
	~RemoteProcessCore();

	vector <ProcessInfo> *getRemoteProcessList();
	void remoteProcessListOperation();
	void remoteProcessAttachOperation(DWORD pid);
	void remoteProcessDetachOperation();
	void terminateCurrentOperation();
	
	BOOL isIdle();

	void setRemoteProcessInterface(RemoteProcessInterface *remoteProcess);
	virtual void onUpdateState(RemoteProcessInterface::State state, BOOL result);

protected:
	virtual void onStarted(RemoteProcessOperation *operation);
	virtual void onFinished(RemoteProcessOperation *operation);
	virtual void onError(RemoteProcessOperation *operation, const TCHAR *msg);
	virtual void onInfo(RemoteProcessOperation *operation, const TCHAR *msg);
	virtual void notifyFinish(RemoteProcessInterface::State state, BOOL result);

private:
	void executeOperation(RemoteProcessOperation *operation) throw(IOException);

	LogWriter *m_logWriter;
	RemoteProcessRequestSender *m_sender;
	RemoteProcessReplyBuffer *m_replyBuffer;
	ListenerContainer<RemoteProcessEventHandler *> *m_remoteProcessListeners;

	LocalMutex m_locker;
	RemoteProcessInterface::State m_state;
	RemoteProcessInterface *m_remoteProcess;
	RemoteViewerCore *m_remoteViewer;
	RemoteProcessOperation *m_currentOperation;
	vector<ProcessInfo> m_remoteProcessInfo;
};
