#ifndef ESP_HPP
#define ESP_HPP

#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;
using namespace std;

class ESP
{
private:
	string portName;
	unsigned int baud_rate;
	bool connected;
	serial_port *serial;

public:
	bool isConnected();
	struct USART_package
	{
		string device; // Button , potentiometer...
		int sizeStr;   // size of the string
		int value;	   // Value of the device
	};

	struct USART_package readUSART();
	void send(string &message);

	ESP(const string &port, unsigned int baud_rate);

	~ESP();
};

#endif