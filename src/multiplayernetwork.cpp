#include "multiplayernetwork.h"
/*
default constructor; sets status to "NONE".
*/
MultiplayerNetwork::MultiplayerNetwork() {
	status = NONE;
	received_message = false;
}

/*
sets up the server (and shutting down the client if it is on); returns whether the setup was successful.
if the setup is successful changes status to "HOST".
*/
bool MultiplayerNetwork::server_setup() {
	client.close();
	status = NONE; 
	received_message = false;
	bool connected = server.setup(kMultiplayerPort);
	if (connected) {
		status = HOST;
		received_message = true;
	}
	return connected;
}

/*
sets up the client to connect to the specified ip address (and shutting down the server if it is on); returns whether the connection was successful.
if the setup is successful changes status to "CLIENT".
*/
bool MultiplayerNetwork::client_setup(string ip_address) {
	server.disconnectAllClients();
	server.close();
	status = NONE;
	received_message = false;
	bool connected = client.setup(ip_address, kMultiplayerPort);
	if (connected) {
		status = CLIENT;
	}
	return connected;
}

/*
close both the server and the client and set status to "NONE".
*/
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

/*
returns whether the program is "connected", defined by either
1. as a client connected to a host
2. as a host have the inital client connected (since the game is between the host and client 0 -
any client other than number 0 is disconnected immediately)
*/
bool MultiplayerNetwork::is_connected() {
	if (status == HOST) {
		return server.isClientConnected(0);
	}
	else if (status == CLIENT) {
		return client.isConnected();
	}
	else {
		return false;
	}
}

/*
send a message through the server or the client based on which one is in use.
*/
void MultiplayerNetwork::send(string message) {
	if (status == HOST) {
		server.send(0, message);
	}
	else if (status == CLIENT) {
		client.send(message);
	}
}

/*
receives a message from the partner. Uses a lossy receiving method.
explanation: sometimes due to lag there will be multiple messages in the buffer when receive() is called at the start of every update.
if only one message is received per update, severe lag will be caused due to messages piling up to form a queue.
this way, only the last message in the queue is actually read; the rest are discarded.
this will cause some loss of data but has miniscule impact on gameplay due to graphics updating 40 times a second - missing a frame or two
here and there will not drastically alter the perception of the graphics.
*/
string MultiplayerNetwork::receive() {
	if (status == HOST) {
		string message = server.receive(0);
		string checker = server.receive(0);
		while (checker.size() > 0 && server.getNumClients() > 0) {
			received_message = true;
			message = checker;
			checker = server.receive(0);
		}
		return message;
	}
	else if (status == CLIENT) {
		string message = client.receive();
		string checker = client.receive();
		while (checker.size() > 0) {
			received_message = true;
			message = checker;
			checker = client.receive();
		}
		return message;
	}
	return "";
}

/*
returns the status enum of the object.
*/
Connection MultiplayerNetwork::get_status() {
	return status;
}

/*
disconnects every client but client 0 from a server. Does nothing if the server is not in use or
if there is exactly one client connected to said server.
*/
void MultiplayerNetwork::disconnect_additional_clients() {
	if (status == HOST && server.getNumClients() > 1) {
		for (int i = 1; i < server.getLastID(); i++) {
			if (server.isClientConnected(i)) {
				server.disconnectClient(i);
			}
		}
	}
}

/*
returns whether a client has received a message from a server in the period of time it was connected to it.
Used to determine whether the client was disconnected due to trying to connect to a server already hosting another client
(as this client will not receive any messages because all messages are sent to client No.0).
*/
bool MultiplayerNetwork::received_message_from_server() {
	return received_message;
}