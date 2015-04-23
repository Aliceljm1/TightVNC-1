#include "RemoteProcessCore.h"


RemoteProcessCore::RemoteProcessCore(LogWriter *logWriter,
	RemoteProcessRequestSender *sender,
	RemoteProcessReplyBuffer *replyBuffer,
	ListenerContainer<RemoteProcessEventHandler *> *pListeners)
	: m_logWriter(logWriter),
	m_sender(sender),
	m_replyBuffer(replyBuffer),
	m_remoteProcessListeners(pListeners),
	m_currentOperation(nullptr), m_state(State::Idle)
{
}

RemoteProcessCore::~RemoteProcessCore()
{
	if (m_currentOperation != nullptr) {
		delete m_currentOperation;
	}
}

void RemoteProcessCore::onStarted(RemoteProcessOperation *operation) {
	// prograte information
}

void RemoteProcessCore::onFinished(RemoteProcessOperation *operation) {
	if (m_state == State::List) {
		auto *processListOperation = dynamic_cast<RemoteProcessListOperation *>(operation);

		if (processListOperation->isOk()) {
			auto numberProcesses = m_replyBuffer->getProcessInfoCount();
			m_remoteProcessInfo.resize(numberProcesses);
			for (auto i = 0; i < numberProcesses; ++i) {
				m_remoteProcessInfo[i] = m_replyBuffer->getProcessInfo()[i];
			}
		}
	}

	// propagate information
}

void RemoteProcessCore::onError(RemoteProcessOperation *operation, const TCHAR *msg) {
	// propagate information
}

void RemoteProcessCore::onInfo(RemoteProcessOperation *operation, const TCHAR *msg) {
	//propagate information
}

void RemoteProcessCore::executeOperation(RemoteProcessOperation *newOperation)
{
	if (m_currentOperation != nullptr) {
		m_currentOperation->removeListener(this);
		delete m_currentOperation;
	}

	m_currentOperation = newOperation;
	m_currentOperation->setRequestSender(m_sender);
	m_currentOperation->setReplyBuffer(m_replyBuffer);
	m_currentOperation->addListener(this);

	try {
		m_currentOperation->start();
	}
	catch (IOException &ioEx) {
		// propagate exception
	}
}

void RemoteProcessCore::remoteProcessListOperation()
{
	m_state = State::List;
	executeOperation(new RemoteProcessListOperation(m_logWriter));
}

vector<ProcessInfo> *RemoteProcessCore::getRemoteProcessList()
{
	return &m_remoteProcessInfo;
}

void RemoteProcessCore::terminateCurrentOperation()
{
}
