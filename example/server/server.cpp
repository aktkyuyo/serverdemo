
#include "socket_io/my_internal_moduel.hpp"
#include <iostream>

class user_module : public my_internal_moduel
{
public:
	void receive_msg(net_id id, const char* data, size_t size) override
	{
		std::cout << "net_id:" << id << " data:" << data << " size:" << size << std::endl;
	}

	void on_connect(net_id id, my_internal_endpoint& endpoint) override{}
	void on_disconnect(net_id id, my_internal_endpoint& endpoint) override{}
};

int main(int argc, char* argv[])
{
	user_module test_center;
	test_center.asny_listen(8989);
	// test_center.asny_listen(7888);
#ifdef _WIN32
	system("pause");
#else
	pause();
#endif // _WINDOWS_

	
	return 0;
}
