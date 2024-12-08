/*Ajouter des entête sous chaque fichier*/

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
	struct USART_package
	{
		string device; // Button , potentiometer...
		int sizeStr;   // size of the string
		int value;	   // Value of the device
	};
	/**
	 * @brief Checks if the ESP device is connected.
	 *
	 * @return true if connected, false otherwise.
	 */
	bool isConnected();

	/**
	 * @brief Reads a message from the USART interface and parses it into a USART_package structure.
	 *
	 * @return ESP::USART_package containing the parsed data.
	 */
	struct USART_package readUSART();

	/**
	 * @brief Sends a message through the USART interface.
	 *
	 * @param message The message to send.
	 */
	void sendUSART(string &message);

	/**
	 * @brief Constructs an ESP object and initializes the USART connection.
	 *
	 * @param port The name of the serial port.
	 * @param baud_rate The baud rate for the USART communication.
	 */
	ESP(const string &port, unsigned int baud_rate);

	/**
	 * @brief Destructor for the ESP class. Cleans up the allocated resources if connected.
	 */
	~ESP();
};

#endif