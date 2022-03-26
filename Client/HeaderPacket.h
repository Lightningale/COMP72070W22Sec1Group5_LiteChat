#pragma once
#include "Packet.h"
class HeaderPacket :public Packet
{
	struct HeaderData
	{
		char response[responseSize];
		int packetNum;//number of packets to follow
	}headerData;

public:
	HeaderPacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&headerData, src + sizeof(Header), sizeof(HeaderData));
	}
	HeaderPacket(const char* response, int packetNum)
	{
		memcpy(headerData.response , response, responseSize);
		headerData.packetNum = packetNum;
		this->SetHeader(typeResponse,"");
		head.size += sizeof(HeaderData);
	}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &headerData, sizeof(headerData));
	}
	char* getResponse()
	{
		return headerData.response;
	}
	int getPacketNum()
	{
		return headerData.packetNum;
	}
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Response:" << headerData.response << endl;

	}
};