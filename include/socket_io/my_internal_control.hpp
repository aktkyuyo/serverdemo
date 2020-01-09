#pragma once

#include <memory>
#include <boost/asio/ip/tcp.hpp>
#include "my_internal_message.hpp"
#include "my_internal_server.hpp"
class my_internal_control : public std::enable_shared_from_this<my_internal_control>
{
	

public:
	my_internal_control(my_internal_server &model_basee_, net_id net_id_,
		boost::asio::ip::tcp::socket &socket_, my_internal_endpoint endpoint_);
	~my_internal_control();

	void send_msg(const char* data, int size);

	void close();

private:
	void real_send_msg(const my_internal_message &msg);
	void receive_msg(const my_internal_message &msg);
	void start();
	void do_write();
	void do_read_header();
	void do_read_body();

	my_internal_server & m_model_base_;
	net_id m_net_id_;
	boost::asio::ip::tcp::socket m_socket_;
	my_internal_endpoint m_endpoint_;
	my_message_queue m_send_msg_list_;
	my_internal_message m_read_msg_;

	std::atomic<std::size_t> m_check_num_;
	std::atomic<std::size_t> m_last_check_num_;
	std::string test_str_;
};
