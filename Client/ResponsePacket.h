#pragma once
#include "Packet.h"
class ResponsePacket :public Packet
{
	struct ResponseData
	{
		char response[responseSize];
	}responseData;

public:
	ResponsePacket(char* src)
	{
		memcpy(&head, src, sizeof(Header));
		memcpy(&responseData, src + sizeof(Header), sizeof(ResponseData));
	}
	//ResponsePacket(char* response)
	//{
	//	memcpy(responseData.response , response, responseSize);
	//}
	//serialize object and store in buffer
	void GetSerializedData(char* buffer)
	{
		memcpy(buffer, &head, sizeof(Header));
		memcpy(buffer + sizeof(Header), &responseData, sizeof(ResponseData));
	}
	char* getResponse()
	{
		return responseData.response;
	}
\
	void Print()
	{
		cout << "Packet type:" << head.type << endl;
		cout << "Response:" << responseData.response << endl;

	}
};