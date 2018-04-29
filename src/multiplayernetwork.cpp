#include "multiplayernetwork.h"
MultiplayerNetwork::MultiplayerNetwork() {
	status = NONE;
}

bool MultiplayerNetwork::server_setup() {
	client.close();
	status = NONE;
	bool connected = server.setup(multiplayer_port);
	if (connected) {
		status = HOST;
	}
	return connected;
}

void MultiplayerNetwork::close() {
	if (status == HOST) {
		server.disconnectAllClients();
		server.close();
		status = NONE;
	}
	else if (status == CLIENT) {
		client.close();
		status = NONE;
	}
}
bool MultiplayerNetwork::client_setup(string ip_address) {
	server.disconnectAllClients();
	server.close();
	status = NONE;
	bool connected = client.setup(ip_address, multiplayer_port);
	if (connected) {
		status = CLIENT;
	}
	return connected;
}

bool MultiplayerNetwork::check_connection() {
	if (status == HOST) {
		return server.getNumClients() > 0;
	}
	else if (status == CLIENT) {
		return client.isConnected();
	}
	else {
		return false;
	}
}

connection MultiplayerNetwork::get_status() {
	return status;
}

vector<string> MultiplayerNetwork::receive() {
	vector<string> message_array;
	if (status == HOST) {
		string message = server.receive(0);
		string checker = server.receive(0);
		while (checker.size() > 0) {
			message = checker;
			message_array.push_back(message);
			checker = server.receive(0);
		}
	}
	else if (status == CLIENT) {
		string message = client.receive();
		string checker = client.receive();
		while (checker.size() > 0) {
			message = checker;
			message_array.push_back(message);
			checker = client.receive();
		}
	}
	return message_array;
}