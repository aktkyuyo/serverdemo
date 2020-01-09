#include "socket_io/my_internal_moduel.hpp"
#include <iostream>
#include <ctime>

class user_moduel : public my_internal_moduel
{
public:
	void receive_msg(net_id id, const char *data, size_t size) override
	{
		std::cout << "net_id:" << id << " data:" << data << " size:" << size << std::endl;
	}

	void on_connect(net_id id, my_internal_endpoint &endpoint) override
	{
		m_net_id.insert(id);
	}
	void on_disconnect(net_id id, my_internal_endpoint &endpoint) override
	{
		is_can_stop = true;
	}

	std::set<net_id> m_net_id;
	bool is_can_stop = false;
};

int main(int argc, char *argv[])
{
	std::string ip_der = "127.0.0.1";
	int port = 8989;

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	user_moduel test_center;

	int test_limit = 1;

	for (int i = 0; i < test_limit; ++i)
	{
		std::rand();
		test_center.asny_connect(port, ip_der);
	}

	std::string line;
	while (std::cin >> line && !test_center.is_can_stop)
	{
		for (auto v : test_center.m_net_id)
		{
			std::string tmp = line;
			for (int i = 0; i < 10; i++)
			{
				test_center.send_msg(v, tmp.c_str(), tmp.size());
			}
		}
	}

	return 0;
}
