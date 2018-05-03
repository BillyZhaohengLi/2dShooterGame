#pragma once
#include "ofMain.h"
#include "../src/const.h"
#include "../game_addons/multiplayernetwork.h"
#include "../game_addons/ofxCenteredTrueTypeFont.h"
#include "UNIT_TEST.h"

/*
unit tests for the multiplayer_network class.
*/
inline void MULTIPLAYER_NETWORK_TESTS() {
	UNIT_TEST MULTIPLAYER_TEST = UNIT_TEST("multiplayer network tests");
	MultiplayerNetwork test_network;

	//the network should be initialized to being disconnected
	MULTIPLAYER_TEST.ASSERT_EQUALS("test initial state", NONE, test_network.get_status());

	//start a server
	MULTIPLAYER_TEST.ASSERT_EQUALS("test server setup", true, test_network.server_setup());

	//the network should be identified as host
	MULTIPLAYER_TEST.ASSERT_EQUALS("test initial state", HOST, test_network.get_status());

	//hosts automatically have received_message set to true
	MULTIPLAYER_TEST.ASSERT_EQUALS("test initial state", true, 
		test_network.received_message_from_server());

	MultiplayerNetwork test_network2;
	//start a server
	MULTIPLAYER_TEST.ASSERT_EQUALS("test conflicting server setup", 
		false, test_network2.server_setup());

	//the network should still be disconnected since the setup failed
	MULTIPLAYER_TEST.ASSERT_EQUALS("test state after failed server setup", 
		NONE, test_network2.get_status());

	//connecting to a bad ip address will fail.
	MULTIPLAYER_TEST.ASSERT_EQUALS("test connection to nonexistent ip address",
		false, test_network2.client_setup("255.255.255.255"));

	//the network should still be disconnected since the setup failed
	MULTIPLAYER_TEST.ASSERT_EQUALS("test state after failed client setup", 
		NONE, test_network2.get_status());

	//connecting to a valid ip address.
	MULTIPLAYER_TEST.ASSERT_EQUALS("test connection to existing ip address",
		true, test_network2.client_setup("127.0.0.1"));
	MULTIPLAYER_TEST.ASSERT_EQUALS("test state after successful client setup", 
		CLIENT, test_network2.get_status());
    
	//both the host and the client will now be connected.
	MULTIPLAYER_TEST.ASSERT_EQUALS("confirm connection host", true, test_network.is_connected());
	MULTIPLAYER_TEST.ASSERT_EQUALS("confirm connection client", true, test_network2.is_connected());

	//client yet has to receive message from server
	MULTIPLAYER_TEST.ASSERT_EQUALS("test client received_message state", 
		false, test_network2.received_message_from_server());

	//test server sending to client
	test_network.send("aaa");
	MULTIPLAYER_TEST.ASSERT_EQUALS("host sending to client", 
		std::string("aaa"), test_network2.receive());

	//the client received a message from the server.
	MULTIPLAYER_TEST.ASSERT_EQUALS("confirm received message from host", 
		true, test_network2.received_message_from_server());

	//test client sending to server
	test_network2.send("bbb");
	MULTIPLAYER_TEST.ASSERT_EQUALS("client sending to host", 
		std::string("bbb") , test_network.receive());

	//test lossy sending
	test_network2.send("xxx");
	test_network2.send("bbb");
	test_network2.send("ddd");
	MULTIPLAYER_TEST.ASSERT_EQUALS("test lossy sending", std::string("ddd"), test_network.receive());

	//test disconnect
	test_network2.close();

	//the network should now be back to being disconnected
	MULTIPLAYER_TEST.ASSERT_EQUALS("test state after disconnect", NONE, test_network2.get_status());

	//the server is no longer "connected" since it no longer has client 0 connected to it.
	MULTIPLAYER_TEST.ASSERT_EQUALS("test server is_connected with no clients", 
		false, test_network.is_connected());

	MultiplayerNetwork test_network3;
	test_network3.client_setup("127.0.0.1");

	//the server is still no longer "connected" since the new client is client 1, not 0.
	MULTIPLAYER_TEST.ASSERT_EQUALS("test server is_connected with clients other than client 0",
		false, test_network.is_connected());

	test_network.disconnect_additional_clients();
	
	//test disconnect by server
	MULTIPLAYER_TEST.ASSERT_EQUALS("test manual disconnect by server", 
		false, test_network3.is_connected());

	//close networks after testing
	test_network.close();
	test_network2.close();
	test_network3.close();
}