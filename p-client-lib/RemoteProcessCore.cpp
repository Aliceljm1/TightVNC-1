#include "RemoteProcessCore.h"


RemoteProcessCore::RemoteProcessCore(LogWriter *logWriter,
	RemoteProcessRequestSender *sender,
	RemoteProcessReplyBuffer *replyBuffer,
	RemoteViewerCore *remoteViewer,
	ListenerContainer<RemoteProcessEventHandler *> *pListeners)
	: m_logWriter(logWriter),
	m_sender(sender),
	m_replyBuffer(replyBuffer),
	m_remoteViewer(remoteViewer),
	m_remoteProcessListeners(pListeners),
	m_currentOperation(nullptr), m_state(RemoteProcessInterface::State::Idle)
{
}

RemoteProcessCore::~RemoteProcessCore()
{
	if (m_currentOperation != nullptr) {
		delete m_currentOperation;
	}
}


void RemoteProcessCore::setRemoteProcessInterface(RemoteProcessInterface *remoteProcess)
{
	AutoLock l(&m_locker);
	m_remoteProcess = remoteProcess;
}


void RemoteProcessCore::onUpdateState(RemoteProcessInterface::State state, BOOL result)
{
	switch (state)
	{
	case RemoteProcessInterface::State::List:
		if (result)
		{
			AutoLock l(&m_locker);
			if (m_remoteProcess)
			{
				m_remoteProcess->setIdleState();
			}
		}

		break;
	default:
		break;
	}
}


void RemoteProcessCore::onStarted(RemoteProcessOperation *operation)
{
	AutoLock l(&m_locker);
	if (m_remoteProcess){
		m_remoteProcess->onOpStarted();
	}
}


void RemoteProcessCore::onFinished(RemoteProcessOperation *operation) {
	BOOL result = TRUE;
	if (m_state == RemoteProcessInterface::State::List) {
		auto *processListOperation = dynamic_cast<RemoteProcessListOperation *>(operation);

		if (processListOperation->isOk()) {
			auto numberProcesses = m_replyBuffer->getProcessInfoCount();
			m_remoteProcessInfo.resize(numberProcesses);
			for (unsigned int i = 0; i < numberProcesses; ++i) {
				m_remoteProcessInfo[i] = m_replyBuffer->getProcessInfo()[i];
			}
		}
		result = processListOperation->isOk();
	}
	else if(m_state == RemoteProcessInterface::State::Detach)
	{
		m_remoteViewer->refreshFullScreen();
	}

	notifyFinish(m_state, result);
	m_state = RemoteProcessInterface::State::Idle;
}


void RemoteProcessCore::notifyFinish(RemoteProcessInterface::State state, BOOL result)
{
	AutoLock l(&m_locker);
	if (m_remoteProcess){
		m_remoteProcess->onOpFinished(m_state, result);
	}

}


void RemoteProcessCore::onError(RemoteProcessOperation *operation, const TCHAR *msg) {
	// propagate information
}


void RemoteProcessCore::onInfo(RemoteProcessOperation *operation, const TCHAR *msg) {
	//propagate information
}


BOOL RemoteProcessCore::isIdle()
{
	return m_state == RemoteProcessInterface::State::Idle;
}


void RemoteProcessCore::executeOperation(RemoteProcessOperation *newOperation)
{
	if (m_currentOperation != nullptr)
	{
		m_currentOperation->removeListener(this);
		m_remoteProcessListeners->removeListener(m_currentOperation);
		delete m_currentOperation;
	}

	m_currentOperation = newOperation;
	m_currentOperation->setRequestSender(m_sender);
	m_currentOperation->setReplyBuffer(m_replyBuffer);
	m_currentOperation->addListener(this);
	m_remoteProcessListeners->addListener(m_currentOperation);

	try
	{
		m_currentOperation->start();
	}
	catch (IOException &ioEx)
	{
		m_remoteProcess->raise(ioEx);
	}
}

void RemoteProcessCore::remoteProcessListOperation()
{
	m_state = RemoteProcessInterface::State::List;
	executeOperation(new RemoteProcessListOperation(m_logWriter));
}


void RemoteProcessCore::remoteProcessDetachOperation()
{
	m_state = RemoteProcessInterface::State::Detach;
	executeOperation(new RemoteProcessDetachOperation(m_logWriter));
}


void RemoteProcessCore::remoteProcessAttachOperation(const DWORD pid)
{
	m_state = RemoteProcessInterface::State::Attach;
	executeOperation(new RemoteProcessAttachOperation(m_logWriter, pid));
}


vector<ProcessInfo> *RemoteProcessCore::getRemoteProcessList()
{
	return &m_remoteProcessInfo;
}

void RemoteProcessCore::terminateCurrentOperation()
{
	m_state = RemoteProcessInterface::State::Idle;
}
