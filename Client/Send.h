#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>

using namespace std;

void sendImage(SOCKET ClientSocket) {
	char filePath[250];
	char TxBuffer[300];

	cout << "Please Enter the file path for the image: "; //Get image file path from user
	cin.getline(filePath, 250);

	ifstream image(filePath, ios::binary); //Create input stream
	if (image.is_open()) {
		image.seekg(0, image.end); //find size of image
		int size = image.tellg();
		image.seekg(0, image.beg);
		vector<char> buffer(size);

		if (image.read(buffer.data(), size)) {

			memcpy(TxBuffer, &size, sizeof(int));
			send(ClientSocket, TxBuffer, sizeof(int), 0);

			for (int x = 0; x < size; x += 300) { //
				if (size - x > 300) {
					for (int i = 0; i < 300; i++) {
						TxBuffer[i] = buffer[x + i];
					}
				}
				else {
					for (int i = 0; i < size - x; i++) {
						TxBuffer[i] = buffer[x + i];
					}
				}
				send(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
			}
		}
		else {
			cout << "failed to open image\n";
		}
	}
	else {
		cout << "failed to open image\n";
	}
}

void recieveImage(SOCKET ClientSocket) {
	char TxBuffer[300];
	char name[300];
	int size = 0;

	recv(ClientSocket, TxBuffer, sizeof(TxBuffer), 0); //recieve size of image
	memcpy(&size, TxBuffer, sizeof(int));
	vector<char> buffer(size);

	for (int x = 0; x < size; x += 300) {
		recv(ClientSocket, TxBuffer, sizeof(TxBuffer), 0);
		if (size - x > 300) {
			for (int i = 0; i < 300; i++) {
				buffer[x + i] = TxBuffer[i];
			}
		}
		else {
			for (int i = 0; i < size - x; i++) {
				buffer[x + i] = TxBuffer[i];
			}
		}

	}

	cout << "Please Enter the name of the image (with image type e.g. .jpg): "; //get image name from user
	cin.getline(name, 250);

	ofstream newImage(name, ios::binary); //create output stream

	ostream_iterator<char> output_iterator(newImage);
	copy(buffer.begin(), buffer.end(), output_iterator);
}