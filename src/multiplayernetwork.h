#pragma once
#include "const.h"
#include "ofMain.h"
#include "ofxNetwork.h"

/*
wrapper class for the TCP server and client in every instance of the program.
*/
class MultiplayerNetwork {
private:
	/*
	TCP server.
	*/
	ofxTCPServer server;

	/*
	TCP client.
	*/
	ofxTCPClient client;

	/*
	the status the program is in; used to determine whether to send/receive messages from the server or the client depending on which one is in use.
	*/
	Connection status;
public:
	/*
	default constructor; sets status to "NONE".
	*/
	MultiplayerNetwork();

	/*
	sets up the server (and shutting down the client if it is on); returns whether the setup was successful.
	if the setup is successful changes status to "HOST".
	*/
	bool server_setup();

	/*
	sets up the client to connect to the specified ip address (and shutting down the server if it is on); returns whether the connection was successful.
	if the setup is successful changes status to "CLIENT".
	*/
	bool client_setup(string ip_address);

	/*
	close both the server and the client and set status to "NONE".
	*/
	void close();

	/*
	returns whether the program is "connected", defined by either
	1. as a client connected to a host
	2. as a host have at least 1 client connected
	*/
	bool is_connected();

	/*
	send a message through the server or the client based on which one is in use.
	*/
	void send(string message);

	/*
	receives a message from the partner. Uses a lossy receiving method.
	*/
	string receive();

	/*
	returns the status enum of the object.
	*/
	Connection get_status();

	/*
	disconnects every client but the first one to connect from a server. Does nothing if the server is not in use or
	if there is exactly one client connected to said server.
	*/
	void disconnect_additional_clients();
};