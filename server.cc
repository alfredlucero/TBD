#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "config_parser.h"

using boost::asio::ip::tcp;

std::string make_daytime_string() {
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

int main(int argc, char* argv[]) {
  try {
  	NginxConfigParser configParser;
  	NginxConfig config;
  	configParser.Parse(argv[1], &config);

    boost::asio::io_service io_service;
    tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), std::stoi(config.statements_[0]->tokens_[1])));
    for (;;) {
      tcp::socket socket(io_service);
      std::cout << "server started" << std::endl;
      acceptor.accept(socket);

      //std::string message = make_daytime_string();
      boost::array<char, 1024> buf;
      boost::system::error_code error;
      std::size_t len = socket.read_some(boost::asio::buffer(buf), error);

      boost::asio::write(socket, boost::asio::buffer(buf, len), error);
      std::cout << "write finished" << std::endl;
    }
  } catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}