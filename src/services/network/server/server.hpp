#ifndef SERVER_HPP
#define SERVER_HPP

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/streambuf.hpp>
#include <memory>
#include <mutex>
#include <vector>

class Server;

class Session : public std::enable_shared_from_this<Session> {
public:
  explicit Session(Server *server, boost::asio::ip::tcp::socket socket);

  void run();

  static void addClient(Server &server, boost::asio::ip::tcp::socket *socket);
  static void removeClient(Server &server, boost::asio::ip::tcp::socket *socket);

private:
  void scheduleRead();
  void readHandler(const boost::system::error_code &errorCode);

  Server *m_server;
  boost::asio::ip::tcp::socket m_socket;
  boost::asio::streambuf m_buffer;
};

class Server : public std::enable_shared_from_this<Server> {
public:
  explicit Server(uint16_t port);
  Server(const Server &) = delete;
  Server &operator=(const Server &) = delete;
  Server(Server &&) = delete;
  Server &operator=(Server &&) = delete;
  virtual ~Server();

  void start();
  void stop();

  static void transmit(boost::asio::ip::tcp::socket *socket, const std::string &message);
  void broadcast(const std::string &message);

  virtual void onConnect(boost::asio::ip::tcp::socket *socket);
  virtual void onDisconnect(boost::asio::ip::tcp::socket *socket);
  virtual void onReceive(boost::asio::ip::tcp::socket *socket, const std::string &message);

  std::vector<boost::asio::ip::tcp::socket *> getClients() const;

private:
  void doAccept();

  friend void Session::addClient(Server &server, boost::asio::ip::tcp::socket *socket);
  friend void Session::removeClient(Server &server, boost::asio::ip::tcp::socket *socket);

  boost::asio::thread_pool m_ioThread;
  boost::asio::io_context m_ioContext;
  boost::asio::ip::tcp::acceptor m_acceptor;
  std::vector<boost::asio::ip::tcp::socket *> m_clients;
  mutable std::mutex m_clientsMutex;
};

#endif // SERVER_HPP
