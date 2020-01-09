#pragma once

#include "my_internal_server.hpp"

class my_internal_moduel: public my_internal_server
{
public:

	void asny_listen(int port, const std::string& addr = std::string("")) override
	{
		my_internal_server::asny_listen(port, addr);
	}

	 void asny_connect(int port, const std::string& addr) override
	 {
		 my_internal_server::asny_connect(port, addr);
	 }

	 void close_accept(std::string& port_) override
	 {
		 my_internal_server::close_accept(port_);
	}

	 void send_msg(net_id id, const char* data, size_t size) override
	 {
		 my_internal_server::send_msg(id, data, size);
	}

	void receive_msg(net_id id, const char* data, size_t size) override = 0;

	void on_connect(net_id id, my_internal_endpoint &endpoint) override = 0;

	void on_disconnect(net_id id, my_internal_endpoint &endpoint) override = 0;
};


