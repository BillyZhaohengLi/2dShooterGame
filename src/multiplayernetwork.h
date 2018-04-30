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
	bool is_connected();
	void send(string message);
	void disconnect_additional_clients();
	connection get_status();
	string receive();
};