#include <gtest/gtest.h>
#include <thread>

#include "networkUtils.hpp"

TEST(Network, BasicConnections) {
  // Create test server
  TestServer server(SERVER_PORT);

  // Create test clients
  TestClient client1;
  TestClient client2;
  TestClient client3;

  // Start server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(server.isConnectTriggered());
  EXPECT_FALSE(client1.isConnected());
  EXPECT_FALSE(client2.isConnected());
  EXPECT_FALSE(client3.isConnected());

  // Connect clients
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client2.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client3.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.isConnectTriggered());
  EXPECT_EQ(server.getClients().size(), 3);
  EXPECT_TRUE(client1.isConnected());
  EXPECT_TRUE(client2.isConnected());
  EXPECT_TRUE(client3.isConnected());

  // Disconnect one client
  client3.disconnect();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.getClients().size() == 2);
  EXPECT_TRUE(client1.isConnected());
  EXPECT_TRUE(client2.isConnected());
  EXPECT_FALSE(client3.isConnected());
}

TEST(Network, TransmitReceive) {
  // Create test server
  TestServer server(SERVER_PORT);

  // Create test clients
  TestClient client1;
  TestClient client2;
  TestClient client3;

  // Start server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Connect clients
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client2.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client3.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Disconnect one client
  client3.disconnect();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Broadcast message from server
  std::string serverMessage = "SERVER MESSAGE";
  server.broadcast(serverMessage);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify message received
  EXPECT_EQ(client1.getLastReceivedMessage(), serverMessage);
  EXPECT_EQ(client2.getLastReceivedMessage(), serverMessage);
  EXPECT_NE(client3.getLastReceivedMessage(), serverMessage);

  // Transmit message from client
  std::string clientMessage = "CLIENT MESSAGE";
  client1.transmit(clientMessage);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify message received
  EXPECT_EQ(server.getLastReceivedMessage(), clientMessage);
}

TEST(Network, ConnectDisconnect) {
  // Create test server
  TestServer server(SERVER_PORT);

  // Create test clients
  TestClient client1;
  TestClient client2;
  TestClient client3;

  // Start server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Stop server
  server.stop();

  // Check connections
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(client1.isConnected());
  EXPECT_FALSE(client2.isConnected());
  EXPECT_FALSE(client3.isConnected());

  // Start server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(client1.isConnected());
  EXPECT_FALSE(client2.isConnected());
  EXPECT_FALSE(client3.isConnected());

  // Connect client1
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_EQ(server.getClients().size(), 1);
  EXPECT_TRUE(client1.isConnected());

  // Disconnect client
  client1.disconnect();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(client1.isConnected());

  // Reconnect client
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_EQ(server.getClients().size(), 1);
  EXPECT_TRUE(client1.isConnected());

  // Disconnect client
  client1.disconnect();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(client1.isConnected());

  // Reconnect client
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Check connections
  EXPECT_EQ(server.getClients().size(), 1);
  EXPECT_TRUE(client1.isConnected());

  // Transmit message
  std::string clientMessage2 = "CLIENT MESSAGE 2";
  client1.transmit(clientMessage2);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify message received
  EXPECT_EQ(server.getLastReceivedMessage(), clientMessage2);
}

// TODO(renda): Verify responses to error cases.

TEST(Network, ErrorCases) {
  // Create test server
  TestServer server(SERVER_PORT);

  // Create test clients
  TestClient client1;
  TestClient client2;
  TestClient client3;

  // Start server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Connect clients
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client2.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client3.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when starting already running server
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when stopping server while clients are connected
  server.stop();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when trying to connect client to stopped server
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when transmitting to stopped server
  client1.transmit("MESSAGE");
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when disconnecting from stopped server
  client1.disconnect();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when broadcasting from stopped server
  server.broadcast("MESSAGE");
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify no crash when stopping already stopped server
  server.stop();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify broken connection
  EXPECT_TRUE(server.getClients().empty());
  EXPECT_FALSE(client1.isConnected());

  // Finally fix all connections
  server.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  client1.connect(SERVER_ADDRESS, SERVER_PORT);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));

  // Verify fixed connections
  EXPECT_EQ(server.getClients().size(), 1);
  EXPECT_TRUE(client1.isConnected());

  // Test communications
  std::string clientMessage3 = "CLIENT MESSAGE 3";
  client1.transmit(clientMessage3);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  EXPECT_EQ(server.getLastReceivedMessage(), clientMessage3);

  std::string serverMessage2 = "SERVER MESSAGE 2";
  server.broadcast(serverMessage2);
  std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_DURATION));
  EXPECT_EQ(client1.getLastReceivedMessage(), serverMessage2);
}
