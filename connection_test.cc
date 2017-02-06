#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "connection.h"

class ConnectionTest : public ::testing::Test {
protected:
    bool handle_read(boost::system::error_code err) {
        NginxConfig config;
        ServerConfig server_config(&config);
        Connection conn(io_service, &server_config);
        return conn.handle_read(err);
    }
    bool close_socket(boost::system::error_code err) {
        NginxConfig config;
        ServerConfig server_config(&config);
        Connection conn(io_service, &server_config);
        return conn.close_socket(err);
    }
    boost::asio::io_service io_service;
};

TEST_F(ConnectionTest, HandleReadSuccess) {
    boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::success);
    EXPECT_TRUE(handle_read(err));
}

TEST_F(ConnectionTest, HandleReadFail) {
    boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::bad_file_descriptor);
    EXPECT_FALSE(handle_read(err));
}

TEST_F(ConnectionTest, CloseSocketSuccess) {
    boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::success);
    EXPECT_TRUE(close_socket(err));
}

TEST_F(ConnectionTest, CloseSocketFail) {
    boost::system::error_code err = boost::system::errc::make_error_code(boost::system::errc::bad_file_descriptor);
    EXPECT_FALSE(close_socket(err));
}
