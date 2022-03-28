#pragma once
#include "Packet.h"
#include <direct.h>
#include <fstream>
#include <filesystem>
#include <string>

#define _CRT_SECURE_NO_WARNINGS

namespace fs = std::filesystem;

// <<summary>> Creates and returns the working directory for chat log files
char* createDirectory()
{
	char* workingDir;

	// Get the current working directory
	if ((workingDir = _getcwd(NULL, 0)) == NULL)
		perror("_getcwd error");

	char* newDir = new char[strlen(workingDir) + strlen("\\ChatLog")];
	memcpy(newDir, workingDir, strlen(workingDir));
	memcpy(newDir + strlen(workingDir), "\\ChatLog", sizeof("\\ChatLog"));

	// check if ChatLog directory exists, if not, create new directory
	if (!fs::is_directory(newDir))
	{
		fs::create_directory(newDir);
	}
	return newDir;
}

// <Summary> Adds packet details to log file
/*
	void chatLog(bool roomType, time_t timestamp, int chatroomID, char* message)

	roomType -> private or public chatroom, true = private, false = public
	timestamp -> time of the sent message
	chatroomID -> chatroom ID number
	userID -> userID number - current username
	message -> message content
			if it's an image just use [image], maybe a link? who knows

	file name format:
		public or private
		chatroomID
*/ 
void chatLog(bool roomType, time_t timestamp, int chatroomID, char* userID, char* message)
{
	char* workingDir = createDirectory();

	// creating chatlog text file
	fstream file;
	string fileName;
	string fullDir(workingDir);

	// if room is private
	if (roomType)
		fileName.append("\\private_");
	else
		fileName.append("\\public_");

	fileName.append(to_string(chatroomID));
	fileName.append(".txt");

	fullDir.append(fileName);

	// opens the file in the directory given, if it doesnt exist the file is created
	file.open(fullDir, fstream::app);

	// writing packet data to the file
		// format: time, user, message
	file << timestamp << endl;
	file << userID << endl;
	file << message << endl;

	file.close();
}