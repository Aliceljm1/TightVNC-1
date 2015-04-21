#pragma once
class RfbGetProcessListClientMessage : public RfbClientToServerMessage
{
public:
	RfbGetProcessListClientMessage();

	void send(RfbOutputGate *output);
};