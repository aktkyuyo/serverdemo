#pragma once

#ifndef __MY_INTERNAL_SERVER__
#define __MY_INTERNAL_SERVER__
#include <set>
#include <map>
#include <boost/asio.hpp>

class my_internal_control;
typedef size_t net_id;

struct my_internal_endpoint
{
	my_internal_endpoint();
	my_internal_endpoint(boost::asio::ip::tcp::endpoint &endpoint_):
	addr(endpoint_.address().to_string()), port(endpoint_.port()){}
	std::string addr;
	int port;
};

class my_internal_io_context
{
public:
	my_internal_io_context();
	virtual ~my_internal_io_context();

	typedef std::shared_ptr<boost::asio::ip::tcp::acceptor> my_acceptor_ptr;
	boost::asio::io_context & io_context() { return m_io_context_; }
protected:

	void run();

	boost::asio::io_context m_io_context_;
	std::thread m_thread_;
	bool m_is_run_;
};

class my_internal_server : public my_internal_io_context
{
public:
	my_internal_server();
	virtual ~my_internal_server();

	virtual void asny_listen(int port_, const std::string& addr = std::string(""));

	virtual void asny_connect(int port, const std::string& addr);

	virtual void close_accept(std::string& port_) ;

	virtual void send_msg(net_id id, const char* data, size_t size);

	virtual void receive_msg(net_id id, const char* data, size_t size) = 0;

	virtual void on_connect(net_id id, my_internal_endpoint &endpoint) = 0;

	virtual void on_disconnect(net_id id, my_internal_endpoint &endpoint) = 0;

private:
 	void do_accept(const my_acceptor_ptr& acceptor_);

	void do_connect(const boost::asio::ip::tcp::resolver::results_type& endpoints);

	void on_socket(boost::asio::ip::tcp::socket& socket_, boost::asio::ip::tcp::endpoint &endpoint_);

	friend class my_internal_control;
	void on_unsocket(net_id net_id, my_internal_endpoint &endpoint_);
private:
	std::map<int, my_acceptor_ptr> m_acceptor_map;
	std::map<net_id, std::shared_ptr<my_internal_control>> m_control_model_map_;
	std::set<net_id> m_reserve_net_id_set;
};

#endif