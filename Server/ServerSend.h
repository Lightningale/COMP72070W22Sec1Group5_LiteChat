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

void sendImage(SOCKET ConnectionSocket) {
	char RxBuffer[300];

	ifstream image("image.jpg", ios::binary); //Create input stream
	if (image.is_open()) {
		image.seekg(0, image.end); //find size of image
		int size = image.tellg();
		image.seekg(0, image.beg);
		vector<char> buffer(size);

		if (image.read(buffer.data(), size)) {

			memcpy(RxBuffer, &size, sizeof(int));
			send(ConnectionSocket, RxBuffer, sizeof(int), 0);

			for (int x = 0; x < size; x += 300) { //
				if (size - x > 300) {
					for (int i = 0; i < 300; i++) {
						RxBuffer[i] = buffer[x + i];
					}
				}
				else {
					for (int i = 0; i < size - x; i++) {
						RxBuffer[i] = buffer[x + i];
					}
				}
				send(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
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

void recieveImage(SOCKET ConnectionSocket) {
	char RxBuffer[300];
	int size = 0;

	recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0); //recieve size of image
	memcpy(&size, RxBuffer, sizeof(int));
	vector<char> buffer(size);

	for (int x = 0; x < size; x += 300) {
		recv(ConnectionSocket, RxBuffer, sizeof(RxBuffer), 0);
		if (size - x > 300) {
			for (int i = 0; i < 300; i++) {
				buffer[x + i] = RxBuffer[i];
			}
		}
		else {
			for (int i = 0; i < size - x; i++) {
				buffer[x + i] = RxBuffer[i];
			}
		}

	}

	ofstream newImage("image.jpg", ios::binary); //create output stream

	ostream_iterator<char> output_iterator(newImage);
	copy(buffer.begin(), buffer.end(), output_iterator);
}