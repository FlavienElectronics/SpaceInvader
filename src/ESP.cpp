
#include "ESP.hpp"

bool ESP::isConnected()
{
    return (this->connected);
}

ESP::USART_package ESP::readUSART()
{
    char c = 0;
    string data;

    while (c != '\n')
    {
        read(*this->serial, buffer(&c, 1));
        data += c;
    }
    struct USART_package package;
    package.device = data.substr(1, 3);
    // cout << "Device " << package.device << endl;
    package.sizeStr = data.size();
    // cout << "Size " << package.sizeStr << endl;

    if (package.device != "BTN")
    {
        try
        {
            package.value = stoi(data.substr(5, package.sizeStr - 1));
            // cout << "Value " << package.value << endl;
        }
        catch (std::exception& e)
        {
            // cout << e.what() << endl;
        }
    }
    else
    {
        package.value = 0;
    }

    return (package);
}

void ESP::sendUSART(string &message)
{
    write(*this->serial, buffer(message));
}

ESP::ESP(const string &port, unsigned int baud_rate)
{
    io_service io;

    this->portName = port;
    this->baud_rate = baud_rate;
    try
    {
        this->serial = new serial_port(io, this->portName);
        cout << "Connexion USART OK : " << endl;
        this->connected = true;

        // Configuration of serial port
        this->serial->set_option(serial_port_base::baud_rate(this->baud_rate));
        this->serial->set_option(serial_port_base::character_size(8));
        this->serial->set_option(serial_port_base::parity(serial_port_base::parity::none));
        this->serial->set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));
    }
    catch (std::exception& e)
    {
        this->connected = false;
        cout << "Erreur connexion USART\n" << e.what() << endl;
    }
}

ESP::~ESP()
{
    if (this->connected == true)
    {
        delete (this->serial);
    }
}
