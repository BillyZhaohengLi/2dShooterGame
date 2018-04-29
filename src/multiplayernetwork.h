#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxNetwork.h"

class MultiplayerNetwork {
private:
	ofxTCPServer server;
	ofxTCPClient client;
	connection status;
public:
	MultiplayerNetwork();
	bool server_setup();
	void close();
	bool client_setup(string ip_address);
	bool check_connection();
	connection get_status();
	vector<string> receive();
};