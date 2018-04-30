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

bool MultiplayerNetwork::is_connected() {
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

void MultiplayerNetwork::send(string message) {
	if (status == HOST) {
		server.send(0, message);
	}
	else if (status == CLIENT) {
		client.send(message);
	}
}

connection MultiplayerNetwork::get_status() {
	return status;
}

string MultiplayerNetwork::receive() {
	if (status == HOST) {
		string message = server.receive(0);
		string checker = server.receive(0);
		while (checker.size() > 0 && server.getNumClients() > 0) {
			message = checker;
			checker = server.receive(0);
		}
		return message;
	}
	else if (status == CLIENT) {
		string message = client.receive();
		string checker = client.receive();
		while (checker.size() > 0) {
			message = checker;
			checker = client.receive();
		}
		return message;
	}
	return "";
}

void MultiplayerNetwork::disconnect_additional_clients() {
	if (status == HOST && server.getNumClients() > 1) {
		for (int i = 1; i < server.getLastID(); i++) {
			if (server.isClientConnected(i)) {
				server.disconnectClient(i);
			}
		}
	}
}