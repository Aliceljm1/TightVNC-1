#include "RfbClientToServerMessage.h"
#include "RfbGetProcessListClientMessage.h"


RfbGetProcessListClientMessage::RfbGetProcessListClientMessage()
{
}

void RfbGetProcessListClientMessage::send(RfbOutputGate *output) {
	AutoLock al(output);
	output->writeUInt8(ClientMsgDefs::GET_PROCESS_LIST);
	output->writeUInt8(0); // padding
	output->writeUInt16(0);
	output->flush();
}